function hourglassSum(arr) {
  let sum = function (i, j) {
    let sum = arr[i + 1][j + 1];
    for (let k = j; k < j + 3; k++) {
      sum += arr[i][k];
      sum += arr[i + 2][k];
    }
    return sum;
  }
  let high = sum(0, 0);
  for (let i = 0; i + 2 < arr.length; i++)
    for (let j = 0; j + 2 < arr[i].length; j++) {
      let s = sum(i, j);
      if (s > high) high = s;
    };
  return high;
}