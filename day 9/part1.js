fs = require("fs");

solve = function(data) {
    var preamble = [];

   

    for (let i = 25; i < data.length; i++) {
        for (let j = i - 25; j != i; j++) {
            preamble.push(data[j]);
        }

        var number = data[i];

        var isValid = false;

        for (let j = 0; j < preamble.length; j++) {
            if (preamble.includes(number - preamble[j])) {
                isValid = true;
                break;
            }
        }

        preamble = [];

        if (!isValid) {
            console.log(number);
            return;
        }
    }
}

fs.readFile("input.txt", "utf8", function(error, data) {
    if (error) {
        console.log(error);
        process.exit();
    }

    solve(data.split("\n")
              .map((x)=>parseInt(x)));
});