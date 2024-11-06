# baca-loadcell
Skrip tersebut digunakan untuk membaca hasil timbangan dari barang yang diletakkan di atas loadcell.
jika ternyata hasil pengukuran tidak sesuai, misalnya HP yg diukut memiliki berat 200gram, tetapi saat di ukur menggunakan loadcell malah 
300 gram, maka coba ubah skrip dibawah ini:
```
float calibration_factor = 950;
```
silahkan dinaikkan atau diturunkan jika sudah pas
