# oqs online!

Sat Nov 05 21:13:30 2016
oqs.ndph.ox.ac.uk is online

---

submit from l151-vlubuntu didn't work - "didn't get json"
should have bombed out at that point, instead of trying to insert into db
POST blocked on oqsweb? nope. happens from q108 (Windows) as well - when test not complete



```
BB Quizzes Backend

db opened. built: Nov 4 2016 17:59:33. 8 params.
Quiz    Actions
Matrix    Start    View responses
Hoops    Start    View responses
Trails    Start    View responses

Not yet implemented...
this is getPayload() in trails.cpp.

tinstruct.iso(): 'ERROR'
tstart.iso(): 'ERROR'
tfinish.iso(): 'ERROR'

responses:

parseResponses():didn't get json
Error parsing JSON sesh_id: 0

done

Trails::insertRecord()
made XEXEC object... added header fields...

Error:

Database error:
 object: XDB
 instance: 3
 ecount: 1
 ecode: 0
 error_txt: parameter XTIME is invalid

Error:

Database error:
 object: XDB
 instance: 3
 ecount: 2
 ecode: 0
 error_txt: parameter XTIME is invalid

Error:

Database error:
 object: XDB
 instance: 3
 ecount: 3
 ecode: 0
 error_txt: parameter XTIME is invalid

Error:

Database error:
 object: XDB
 instance: 3
 ecount: 4
 ecode: 4
 error_txt: IIAPI_ST_ERRORInfo: ERROR '22008' 4302: '-1/-1/-0001 -01:-01:-01' is not a valid date/time value.
 svr_id_error     = 34078728
 svr_local error  = 4302
 svr_id_server    = 28457
 svr_server_type  = 0
 svr_severity     = IIAPI_SVR_DEFAULT ( 0x0 )
    : 'Sat Nov  5 21:08:09 2016 E_US10CE_4302    '-1/-1/-0001 -01:-01:-01' is not a valid date/time value.'

insert did not succeed...

Error:

Database error:
 object: XDB
 instance: 2
 ecount: 1
 ecode: 5
 error_txt: IIAPI_ST_FAILUREInfo: ERROR '25000' 13172740: The requested operation cannot be performed with active queries.

Error:

Database error:
 object: XDB
 instance: 2
 ecount: 2
 ecode: 5
 error_txt: IIAPI_ST_FAILUREInfo: ERROR '25000' 13172739: The requested operation cannot be performed with active transactions.


```
