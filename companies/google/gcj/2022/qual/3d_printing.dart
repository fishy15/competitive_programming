import 'dart:io';
import 'dart:math';

void main() {
  var t = int.parse(stdin.readLineSync()!);

  for (var i = 1; i <= t; i++) {
    stdout.write("Case ${i}: ");
    solve();
  }
}

void solve() {
  var first = stdin.readLineSync()!.split(" ").map(int.parse).toList();
  var second = stdin.readLineSync()!.split(" ").map(int.parse).toList();
  var third = stdin.readLineSync()!.split(" ").map(int.parse).toList();

  var ok = [0, 0, 0, 0];
  for (var i = 0; i < 4; i++) {
    ok[i] = min(min(first[i], second[i]), third[i]);
  }

  var ans = [0, 0, 0, 0];
  var need = 1000000;
  for (var i = 0; i < 4; i++) {
    ans[i] = min(ok[i], need);
    need -= ans[i];
  }

  if (need > 0) {
    stdout.writeln("IMPOSSIBLE");
  } else {
    stdout.writeln("${ans[0]} ${ans[1]} ${ans[2]} ${ans[3]}");
  }
}
