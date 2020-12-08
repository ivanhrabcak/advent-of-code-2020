import java.io.File

var data: List<String> = File("input.txt").readText()
        .split("\n\n")

var counter: Int = 0


//for (i in 0 until 26) {
//    val letter: Char = 'a' + i
//    for (groupString in data) {
//        val group = groupString.split("\n")
//        var hasSameAnswers = true
//        for (answer: String in group) {
//            if (!answer.contains(letter)) hasSameAnswers = false
//        }
//        println("has group $group $letter?: $hasSameAnswers")
//        println("the counter is $counter")
//        if (hasSameAnswers) {
//            counter++
//        }
//    }
//}
var globalCounter = 0

for (groupString in data) {
    val group = groupString.split("\n")
    var groupCounter = 0
    for (i in 0 until 26) {
        val letter: Char = 'a' + i
        var hasGroupSameAnswers = true
        for (answer: String in group) {
            if (!answer.contains(letter))
                hasGroupSameAnswers = false
        }

        if (hasGroupSameAnswers) {
            groupCounter++
        }
    }
    println("group $group has $groupCounter same answers")
    globalCounter += groupCounter
}

println("globalCounter: $globalCounter")