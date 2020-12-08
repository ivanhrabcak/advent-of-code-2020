import java.io.File
import java.util.*
import java.util.function.Consumer

var data: List<String> = File("input.txt").readText()
        .split("\n\n")

var counter = 0
for (group in data) {
    val answers = group.split("\n")
    for (i in 0 until 26) {
        val letter = 'a' + i
        var allContain = true
        for (answer in answers) {
            if (!answer.contains(letter)) allContain = false
        }
        if (allContain) {
            counter++
        }
    }
}

println(counter)