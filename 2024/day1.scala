import scala.collection.mutable.ArrayBuffer
import scala.io.Source.fromFile

object Main {
  def main(args: Array[String]): Unit = {
    val list1 = ArrayBuffer[Int]()
    val list2 = ArrayBuffer[Int]()

    val inputFile = fromFile("./input/day1.txt")
    try {
        val lines = inputFile.getLines
        while(lines.hasNext) {
            val Array(num1, num2) = lines.next.split("   ")
            list1 += num1.toInt
            list2 += num2.toInt
        }
    } finally inputFile.close
    
    val zippedList = list1.sorted zip list2.sorted
    val sumOfDistances = zippedList.map(x => (x(0) - x(1)).abs).sum
    println(s"part1: $sumOfDistances")

    val freq = list2.groupMapReduce(num => num)(_ => 1)(_ + _)
    val similarityScore = list1.map(num => num * freq.getOrElse(num, 0)).sum
    println(s"part2: $similarityScore")
  }
}