import java.io.File
import java.util.*
import java.util.function.Consumer

var unparsedData: List<String> = File("input.txt").readText()
        .split("\n\n")

var data: Array<String> = Array(unparsedData.size) { i -> unparsedData[i] };

fun getAllYesQuestions(answers: String): MutableList<Char> {
    val out: MutableList<Char> = mutableListOf()

    val sameAnswers: Array<Int> = Array(26) { 0 }
    val allPeopleAnswers: List<String> = answers.split("\n");

    for (answer: String in allPeopleAnswers) {
        for (char: Char in answer.toCharArray()) {
            sameAnswers[char - 'a'] += 1
        }
    }

    for (i: Int in sameAnswers.indices) {
        if (sameAnswers[i] != 0) {
            out.add('a' + i)
        }
    }
    return out
}

var sum: Int = 0

for (answers: String in data) {
    sum += getAllYesQuestions(answers).size
}

println(sum)