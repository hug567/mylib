/*
 * JavaScript练习：
 * 运行环境：Ununtu 18.04, node.js v12.13.1
 * 运行命令：node test.js
 * 2020-09-16
 */

function searchFiles() {
    var fso = new ActiveXObject("Scripting.FileSystemObject");
    var f = fso.GetFolder(document.all.fixfolder.value);
    var fc = new Enumerator(f.files);
    var s = "";
    for (; !fc.atEnd(); fc.moveNext()) {
        s += fc.item();
        s += "<br/>";
    }
    fk = new Enumerator(f.SubFolders);
    for (; !fk.atEnd(); fk.moveNext()) {
        s += fk.item();
        s += "<br/>";
    }

    //textarea.innerHTML = s
    console.log(s);
}

console.log("hello world");
searchFiles();
