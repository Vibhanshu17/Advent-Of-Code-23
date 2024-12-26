import scala.io.Source.fromFile
import scala.collection.mutable.StringBuilder
import scala.util.matching.Regex

object Main {
  def getMultiplyResult(patternMatch: String): Integer = {
    patternMatch.slice(4, patternMatch.size-1).split(',').toList.map(_.toInt).reduce(_ * _)    
  }
  
  def parseMul(s: String, enableDoDont: Boolean = false): Integer = {
    val pattern: Regex = "mul\\(([0-9]+),([0-9]+)\\)".r
    pattern.findAllMatchIn(s).map(x => getMultiplyResult(x.toString)).toList.reduce(_ + _)
  }

  def main(args: Array[String]): Unit = {
    var programString = new StringBuilder("")
    val inputFile = fromFile("./input/day3.txt")
    try {
      val lines = inputFile.getLines
       while(lines.hasNext) {
           programString ++= lines.next
       }
    } finally inputFile.close
    val sumOfMultiplications = parseMul(programString.toString)
    val sumOfMultiplications2 = parseMul(programString.toString, true)
    println(s"part1: $sumOfMultiplications")
    println(s"part2: $sumOfMultiplications2")
  }
}
