

### Snap quiz (Cardiff) auto form submit

```html
  <form id="form1" class="viz" action="https://trials.ctsu.ox.ac.uk/~webfu/HMDB3/StoreData.php" method="post">
    <div>
      <input type="hidden" name="sid" value="1">
      <input type="hidden" name="pid" value="213421343">
      <input type="hidden" name="lsq" value="661">
      <input type="hidden" name="seqord" value="3">
      <input type="hidden" name="studytypeuid" value="1002">
      <input type="hidden" id="timererror" name="timererror" value="-1">
      <input type="hidden" id="performaceTimer" name="performaceTimer" value="-1">
      <input type="hidden" name="datestarted" value="2016-02-29 14:47:31 GMT">
      <input type="hidden" id="abandon" name="abandon" value="0">
      <input type="hidden" id="mean" name="mean" value="-1">
      <input type="hidden" id="demoelapsed" name="demoelapsed" value="-1">
      <input type="hidden" id="totelapsed" name="totelapsed" value="-1">
      <input type="hidden" id="testelapsed" name="testelapsed" value="-1">
      <input type="hidden" id="responses" name="responses" value="">
    </div>
  </form>
```

then this kind of stuff to fill it in:

```js
function writeValue(id, value) {
    document.getElementById(id).value = value;
}

//check all timers for possible dodgeyness.
    var possibleE = test_timer.gethasPossibleError() + reaction_timer.gethasPossibleError() + demo_timer.gethasPossibleError() + total_timer.gethasPossibleError();
    if (possibleE > 0)
        possibleE = 1;

    writeValue("timererror",possibleE); // document.getElementById(id).value = value;
    writeValue("performaceTimer",total_timer.gethasPerformance());

    document.getElementById("responses").value = JSON.stringify(returnData);
    window.onbeforeunload = null;
    document.getElementById("form1").submit();
```