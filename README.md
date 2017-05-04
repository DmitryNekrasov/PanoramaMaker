# Panorama Maker
### Консольное приложение для склейки панорам.

Приложение нужно запускать с двумя параметрами:

* `path` - Путь до каталога с фотографиями
* `mask` - Маска файлов

**Пример:**
```
PanoramaMaker --path=/Users/ScanNorOne/Documents/PanoramaMaker/NSU --mask=*.jpg
```
Информацию о параметрах можно получить, запустив приложение с параметром `help`.

Панорама сохраняется в файл `<имя_каталога>_panorama.jpg` рядом с каталогом фотографий.

**Важно!**
Для корректной работы программы необходимо, чтобы изображения, которые будут склеиваться в панораме слева направо, 
были отсортированы в лексикографическом порядке.

**Пример работы программы:**

<html>
  <p align="center">
    <img src="https://github.com/DmitryNekrasov/PanoramaMaker/blob/master/NSU/IMG_20161105_122006.jpg" height="230">
    <img src="https://github.com/DmitryNekrasov/PanoramaMaker/blob/master/NSU/IMG_20161105_122009.jpg" height="230">
    <img src="https://github.com/DmitryNekrasov/PanoramaMaker/blob/master/NSU/IMG_20161105_122011.jpg" height="230">
    <img src="https://github.com/DmitryNekrasov/PanoramaMaker/blob/master/NSU/IMG_20161105_122014.jpg" height="230">
    <img src="https://github.com/DmitryNekrasov/PanoramaMaker/blob/master/NSU/IMG_20161105_122016.jpg" height="230">
    <img src="https://github.com/DmitryNekrasov/PanoramaMaker/blob/master/NSU_panorama.jpg" height="235">
  </p>
<html>
