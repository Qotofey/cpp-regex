# Инструкция
Для запуска проекта требуется VirtualBox и Vagrant
```bash
brew cask install virtualbox
brew install vagrant
```
Клонируем проект и запускаем рабочее окружение 
```bash
vagrant up
```
После заврешения заходим в наше рабочее окружение
```bash
vagrant ssh
```
И переходим в подкаталог проекта `~/calc/build/`
```bash
cd ~/calc/build/
```
Далее собираем проект
```bash
conan install ..
cmake ..
make
```
Проверяем
```bash
echo "20 100" | ./bin/calc "(X + 10) * lg(Y)"
```
