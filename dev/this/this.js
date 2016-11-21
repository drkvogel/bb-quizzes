
// http://javascriptissexy.com/understand-javascripts-this-with-clarity-and-master-it/

var person = {
    firstName: "Penelope",
    lastName: "Barrymore",
    fullName: function () {
        // Notice we use "this" just as we used "he" in the example sentence earlier?:​
        console.log(this.firstName + " " + this.lastName);
        // We could have also written this:​​
        console.log(person.firstName + " " + person.lastName);
        //console.log(firstName + " " + lastName); // ReferenceError: firstName is not defined
    }
}

person.fullName();
