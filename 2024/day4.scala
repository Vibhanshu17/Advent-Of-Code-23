import scala.io.Source.fromFile

object Main {
    def findAllXmas(words: Array[String]): Integer = { // TODO
        0
    }
    def findAllX_Mas(words: Array[String]): Integer = { // TODO
        0
    }

    def main(args: Array[String]): Unit = {
        var words = Array[String]()
        val inputFile = fromFile("./input/day4ex.txt")
        try {
            val lines = inputFile.getLines
            while(lines.hasNext) {
                words ++= lines
            }
        } finally inputFile.close
        println(words.toList)
        val xmasCounts = findAllXmas(words)
        val x_masCounts = findAllX_Mas(words)
        println(s"part1: $xmasCounts")
        println(s"part2: $x_masCounts")
    }
}