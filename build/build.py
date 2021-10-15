
from distutils.spawn import find_executable
import requests, zipfile, io, os, shutil
import re
import subprocess
import sys
import getopt

PWD_DIR = os.getcwd() + "\\"


ROOT_DIR = PWD_DIR + "..\\"

BIN_DIR= ROOT_DIR + "bin\\"
LIB_DIR= ROOT_DIR + "lib\\"
INCLUDE_DIR= ROOT_DIR + "include\\lnr"
PROJECT_DIR= ROOT_DIR + "prj\\"

msvcCompiler = None


def CreateDirectory(directory):
        if not os.path.exists(directory):
                os.makedirs(directory)

def DeleteDirectory(directory):
        if os.path.exists(directory):
                shutil.rmtree(directory, ignore_errors=True)

def CopyFile(src, dest):
        shutil.copy(src, dest)

def CopyDirectory(srcDir, destDir):
    if not os.path.exists(destDir):
        shutil.copytree(srcDir, destDir)

def SetVisualStudioEnvironment():
    vswhereCmd = ["%ProgramFiles(x86)%\\Microsoft Visual Studio\\Installer\\vswhere.exe", "-latest", "-property", "installationPath"]

    try:
        vsInstalationPath = subprocess.check_output(vswhereCmd, shell=True).decode();
        vsCmdBat ='"%s\\Common7\\Tools\\VsDevCmd.bat" && echo "~~~~VS_ENVIRONMENT_START~~~~" && set'%(vsInstalationPath.rstrip())

        env = (subprocess.Popen(vsCmdBat, shell=True, stdout=subprocess.PIPE)
                     .stdout
                     .read()
                     .decode('utf-8')
                     .splitlines())

        record = False
        for e in env:
          if record == True:
              e = e.strip().split('=')
              os.environ[e[0]] = e[1]
          elif e.strip() == '"~~~~VS_ENVIRONMENT_START~~~~"': 
              record = True

        output = vsInstalationPath
        status = True;
    except CalledProcessError as e:
        output = e.output.decode();
        status = False;
    return status;
       

def GetVisualStudioVersion():
    global msvcCompiler
    
    SetVisualStudioEnvironment();
    if msvcCompiler is None:
            msvcExe = find_executable('cl')
            if msvcExe:
                match = re.search(
                    "(\d+).(\d+)", 
                    os.environ.get("VisualStudioVersion", ""))
                if match:
                    msvcCompiler = int(match.groups()[0])

    return msvcCompiler

def RunCMake(sourcePath = "", installDir = "", prjPath = "", options = None, buildTests = False):
    visualStudioVersion = GetVisualStudioVersion()
    if visualStudioVersion is None:
        raise Exception( "Please run build.py script in Visual Studio Developer Command Prompt")

    print('VS version "{ver}"'.format(ver=visualStudioVersion))


    if visualStudioVersion == 16:
        generator = "Visual Studio 16 2019"
    elif visualStudioVersion == 15:
        generator = "Visual Studio 15 2017 Win64"
    else:
        raise Exception( "Visual studio version is not supported" )

    if not sourcePath:
        sourcePath = ".\\"

    if not prjPath:
        prjPath = sourcePath + "prj\\"

    if not installDir:
        installDir = sourcePath + "bin\\"   

    print("*********************************************")
    print("generetor: {var}".format(var=generator))
    print("source: {var}".format(var=sourcePath))
    print("project path: {var}".format(var=prjPath))
    print("install dir: {var}".format(var=installDir))
    print("*********************************************")

    cmakeCmd = ["cmake.exe",
                "-G", generator,
                "-S", sourcePath,
                "-B", prjPath,
                "-DBUILD_SHARED_LIBS=ON",
                "-DCMAKE_INSTALL_PREFIX=" + installDir
                ]
    if buildTests:
        cmakeCmd.append("-DLNR_BUILD_TESTING=ON");

    if options is not None:
        cmakeCmd = cmakeCmd + options

    subprocess.check_call(cmakeCmd, stderr=subprocess.STDOUT, shell=True)

    config="Debug"        
    cmakeCmd = ["cmake.exe",
                "--build", prjPath,
                "--config", config,
                "--target", "install"
                ]
    
    subprocess.check_call(cmakeCmd, stderr=subprocess.STDOUT, shell=True)

def RunExecutable(cmd):
    subprocess.check_call(cmd, stderr=subprocess.STDOUT, shell=True)

try:
        arguments, values = getopt.getopt(sys.argv[1:],['"ho:v"'], ['tests', 'install-dir=', 'proxy='])
except getopt.GetoptError as err:
        print(err)
        sys.exit(2)

installPath = "";
isBuildTests = False;

for currentArgument, currentValue in arguments:
    if currentArgument == "--tests":
        isBuildTests = True
    elif currentArgument == "--install-dir":
        if currentValue[-1] != '\\' or not '/':
                BIN_DIR = currentValue + '\\'
        else:
                BIN_DIR = currentValue
        installPath = BIN_DIR

try:
        CreateDirectory(BIN_DIR)
        CreateDirectory(LIB_DIR)
        CreateDirectory(INCLUDE_DIR)


        RunCMake(ROOT_DIR, installDir = installPath, buildTests = isBuildTests)

        if isBuildTests:
                RunExecutable( BIN_DIR + "tests")
except ValueError as err:
        print(err.args)
