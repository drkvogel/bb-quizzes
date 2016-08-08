#!/bin/bash -xv

# run_smsd.sh
#
# wrapper script for the SMS system 'daemon', smsd, that tests the exit code of the program
# and allows a certain number of fails before sending warning emails and texts

# allow big core dumps
ulimit -c unlimited

#LIVE_OR_TEST="live"

# the number of consecutive that will trigger warning messages
NUM_FAILS=5

if [ $LIVE_OR_TEST = "live" ]; then
    TARGET_PATH="/user/smsdb/run/"
    EMAIL_RECIPIENTS="corprog@ctsu.ox.ac.uk michael.lay@ctsu.ox.ac.uk clive.berry@ctsu.ox.ac.uk"

    # the contents of the email that gets sent to sms@messaging.clickatell.com
    # which should result in a text message being sent to the number specified in the to: field
    # (see the SMTP API specification at www.clickatell.com)
    SMS_EMAIL_UP=$TARGET_PATH"smtp_sms_up_live.txt"
    SMS_EMAIL_DN=$TARGET_PATH"smtp_sms_dn_live.txt"
else
    TARGET_PATH="/user/smsdb/runtest/"
    EMAIL_RECIPIENTS="chris.bird@ctsu.ox.ac.uk"
    SMS_EMAIL_UP=$TARGET_PATH"smtp_sms_up_test.txt"
    SMS_EMAIL_DN=$TARGET_PATH"smtp_sms_dn_test.txt"
fi

TARGET_PROG="smsd"
TARGET=$TARGET_PATH$TARGET_PROG
STATUS_FILE="run_smsd.status"
LOG_FILE="run_smsd.log"

NOW=$(date)

echo TARGET=$TARGET
echo SMS_EMAIL_UP=$SMS_EMAIL_UP
echo STATUS_FILE=$STATUS_FILE

cd $TARGET_PATH

# STATUS - 0 = running OK; 1 = failed once since running OK; 2 = failed 2 or more times in a row

if [ -f $STATUS_FILE ]; then
    while read inputline   
    do
        STATUS="$(echo $inputline | cut -d, -f1)"
    done < $STATUS_FILE
else
    echo "$NOW: Status file $STATUS_FILE not found" >> $LOG_FILE; STATUS=0
    echo "0" > $STATUS_FILE
fi

#STATUS='expr $STATUS + 1' #ignore
echo status=$STATUS

$TARGET 1>$TARGET_PATH"smsd_error.log";

EXIT_STATUS=$?

echo EXIT_STATUS=$EXIT_STATUS; #>> $LOG_FILE;
    
if [ $EXIT_STATUS -eq 0 ]; then
    # run OK
    echo 0 > $STATUS_FILE
    #echo "$NOW: $TARGET ran successfully" >> $LOG_FILE
    if [ $STATUS -eq 4 ]; then
        # was down, now back up - notify
        echo "$NOW: $TARGET ran successfully after failure" >> $LOG_FILE
        echo "$NOW: Sending OK emails/text" >> $LOG_FILE
        echo -e "SMS delivery system OK on dune: $TARGET exited with status 0.\n$NOW" | mail -s "SMS System - UP" $EMAIL_RECIPIENTS
        cat $SMS_EMAIL_UP | mail -s "SMS System - UP" sms@messaging.clickatell.com chris.bird@ctsu.ox.ac.uk;
    fi
elif [ $STATUS -lt $NUM_FAILS ]; then
    # allow a few fails
    ((STATUS++))
    echo $STATUS > $STATUS_FILE
    echo "$NOW: $TARGET fails: $STATUS 0" >> $LOG_FILE
else
    # already had one fail
    echo "$NOW: $TARGET did not exit with status 0, again" >> $LOG_FILE
    if [ $STATUS -eq $NUM_FAILS ]; then
        # first time has failed twice - send warning
        echo "$NOW: Sending warning emails/text" >> $LOG_FILE
        echo -e "Problem with SMS delivery system on dune: $TARGET did not exit with status 0, twice.\n$NOW" | mail -s "SMS System - DOWN" $EMAIL_RECIPIENTS
        cat $SMS_EMAIL_DN | mail -s "SMS System - DOWN" sms@messaging.clickatell.com chris.bird@ctsu.ox.ac.uk;
    fi
    ((STATUS++))
    echo $STATUS > $STATUS_FILE
fi

exit 0
