import scala.io.Source.fromFile
import scala.collection.mutable.ArrayBuffer

object Main {
  def isReportSafe(nums: Array[Int]): Boolean = {
    val bounded = nums.sliding(2, 1).map{case Array(x, y) => {1<=(x-y).abs && (x-y).abs<=3}}.reduce(_ & _)
    val nonDecreasing = nums.sliding(2, 1).map(pair => pair(0) <= pair(1)).reduce(_ & _)
    val nonIncreasing = nums.sliding(2, 1).map(pair => pair(0) >= pair(1)).reduce(_ & _)
    return (bounded & (nonDecreasing | nonIncreasing))
  }

  def main(args: Array[String]): Unit = {
    var safeReportCount, safeReportsCountExceptOne = 0
    val inputFile = fromFile("./input/day2.txt")
    try {
        val lines = inputFile.getLines
        while(lines.hasNext) {
            val nums = lines.next.split(" ").map(_.toInt)
            if(isReportSafe(nums))
                safeReportCount += 1
                safeReportsCountExceptOne += 1
            else
                val len = nums.size
                safeReportsCountExceptOne += { if((0 until len).map(i => isReportSafe(nums.slice(0, i)++(nums.slice(i+1, len)))).exists(_ == true)) 1 else 0 }
        }
    } finally inputFile.close
    println(s"part1: $safeReportCount")
    println(s"part2: $safeReportsCountExceptOne")
  }
}