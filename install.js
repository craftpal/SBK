var objShell = WScript.CreateObject("WScript.Shell");
var fso = new ActiveXObject("Scripting.FileSystemObject");
var strSavePath = objShell.CurrentDirectory + "\\最適化骨くん.lnk";
var objShortCut = objShell.CreateShortcut(strSavePath);
objShortCut.TargetPath = objShell.CurrentDirectory + "\\GenInputJSON.exe";
objShortCut.WorkingDirectory = objShell.CurrentDirectory;
objShortCut.IconLocation = objShell.CurrentDirectory + "\\hone.ico, 0";
objShortCut.Save();
if (fso.FileExists(strSavePath)) {
  WScript.Echo("インストールは正常に完了しました")
} else {
  WScript.Echo("インストール中に異常が発生しました")
}