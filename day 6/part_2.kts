import java.io.File
import java.util.*
import java.util.function.Consumer

var unparsedData: List<String> = File("input.txt").readText()
        .split("\n\n")

var data: Array<String> = Array(unparsedData.size) { i -> unparsedData[i] };

fun getAllYesQuestions(answers: String): MutableList<Int> {
    val out: MutableList<Int> = mutableListOf()

    val sameAnswers: Array<Int> = Array(26) { 0 }
    val allPeopleAnswers: List<String> = answers.split("\n");

    for (answer: String in allPeopleAnswers) {
        for (char: Char in answer.toCharArray()) {
            sameAnswers[char - 'a'] += 1
        }
    }

    for (i in sameAnswers.indices) {
        if (sameAnswers[i] == allPeopleAnswers.size) {
            out.add(i)
        }
    }
    return out
}

var sum: Int = 0

for (answers: String in data) {
    sum += getAllYesQuestions(answers).size
}

println(sum)