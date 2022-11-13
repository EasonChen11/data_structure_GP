# data_structure_GP
目的: 資料結構專案

參與者: Eason, 江若慈,楊婷羽

## 命名規則
* **function name** :Pascal case
>每個單字第一個字母大寫
>>UserName, FileName
* **local variable and variables inside the structure** :Camel Case
>每個單字第一個字母大寫，除了第一個字以外
>>userName, fileName
* **other** :Snake Case
>每個字母皆為小寫，單字間用'_'相連
>>user_name, file_name

## GIT分支命名方式

開發者/fix_xxx_or_add_yyy_function

example:
`eason/新增專案功能設計文件`

## commit的命名方式

[開發者][issue號碼-功能或修復的問題]

example:
[eason][4-新增專案功能設計文件]


## 使用GIT開發流程

0. 空的資料夾第一次pull
```
git clone https://github.com/EasonChen11/data_structure_GP.git .
```
*只有第一次需要這麼做*

1. 切到main
```
git checkout main
```

2. Pull
```
git pull
```

3. 開分支
```
git branch [branch name]
```
*遵守前面所規定的名稱*

4. 切到分支
```
git checkout [branch name]
```

5. 開發程式

6. commit
```
git add .
git commit -m "[commit messege]"
```
*遵守前面commit的規則*

7. Push
```
git push --set-uptream origin [branch name]
```

8. Pull Request
    1. 點選GitHub上面' pull request'
    2. 點選' new request'
    3. 在敘述欄寫入連結的issue

       ```# [issue number]```
       
    4. 下面點選' merge request'

---
Note:
PR合併到main後, 分支會自動刪除.

