import java.util.ArrayList
import java.util.function.Consumer
import scala.io.StdIn
import scala.math.min

object Solution {
  def main(args: Array[String]): Unit = {
    val t = StdIn.readInt()

    for (i <- 1 to t) {
      print(s"Case #$i: ")
      solve()
    }
  }

  def solve(): Unit = {
    val n = io.StdIn.readInt()

    val f_partial = StdIn.readLine().split(" ").map(x => x.toInt).toArray
    val f = Array(0) ++ f_partial
    val p = StdIn.readLine().split(" ").map(x => x.toInt).toArray

    var adj = new Array[ArrayList[Integer]](n + 1)
    for (i <- 0 to n) {
      adj(i) = new ArrayList[Integer]
    }

    for (i <- 0 to n - 1) {
      adj(p(i)).add(i + 1)
    }

    var ans = dfs(0, 0, f, adj)
    println(ans._1);
  }

  def dfs(
      v: Int,
      p: Int,
      f: Array[Int],
      adj: Array[ArrayList[Integer]]
  ): (Int, Int) = {
    var ans = 0
    var totMin = 0x3f3f3f3f

    adj(v).forEach(new Consumer[Integer] {
      override def accept(e: Integer) {
        if (e != p) {
          var (sum, curMin) = dfs(e, v, f, adj)

          ans += sum
          totMin = min(totMin, curMin)
        }
      }
    })

    if (ans == 0) {
      return (f(v), f(v))
    } else if (totMin < f(v)) {
      ans -= totMin
      ans += f(v)
      totMin = f(v)
    }

    return (ans, totMin)
  }
}
