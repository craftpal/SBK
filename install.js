var objShell = WScript.CreateObject("WScript.Shell");
var fso = new ActiveXObject("Scripting.FileSystemObject");
var strSavePath = objShell.CurrentDirectory + "\\�œK��������.lnk";
var objShortCut = objShell.CreateShortcut(strSavePath);
objShortCut.TargetPath = objShell.CurrentDirectory + "\\GenInputJSON.exe";
objShortCut.WorkingDirectory = objShell.CurrentDirectory;
objShortCut.IconLocation = objShell.CurrentDirectory + "\\hone.ico, 0";
objShortCut.Save();
if (fso.FileExists(strSavePath)) {
  WScript.Echo("�C���X�g�[���͐���Ɋ������܂���")
} else {
  WScript.Echo("�C���X�g�[�����Ɉُ킪�������܂���")
}