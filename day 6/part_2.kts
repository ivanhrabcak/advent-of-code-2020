import java.io.File
import java.util.*
import java.util.function.Consumer

var data: List<String> = File("input.txt").readText()
        .split("\n\n")

var sum = 0

for (i in 0 until 26) {
    val char: Char = 'a' + i
    for (group: String in data) {
        var hasGroupSameAnswers = true
        for (answer: String in group.split("\n")) {
            if (answer.contains(char))
                hasGroupSameAnswers = false
        }
        if (hasGroupSameAnswers)
            sum++
    }
}

println(sum)
