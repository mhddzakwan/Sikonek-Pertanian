# mobil-detekwarna
skrip ini untuk menjalankan mobil sambil mendeteksi warna, jika terdeteksi warna putih, maka mobil akan berhenti. pendeteksian warna dapat di kustomisasi melalui skrip berikut:

```
  if (redFrequency > 40 && redFrequency < 75 && greenFrequency > 42 && greenFrequency < 85 && blueFrequency > 30 && blueFrequency < 73){   
    stop();
  }else{
    forward();
  }
```
kita meletakkan RGB yg diperoleh. bagaimana cara mendapatkan nilai RGB dari warnanya?, buka skrip Baca-Warna.ino, jalankan,
lalu arahkan sensor ke warna yg ingin dideteksi. pertama letakkan sensor dekat dengan permukaan benda yg ingin dideteksi warnanya
lalu catat nilai R G B nya, setelah itu beri jarak agak jauh antara sensor dengan benda (kira"sejengkal tangan), catat nilai R G B nya,

stelah itu buat pengkondisian seperti kode diatas untuk mendeteksi warnanya
