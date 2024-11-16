/* eslint-disable prefer-regex-literals */
/* eslint-disable @typescript-eslint/no-require-imports */

const fs = require("fs");
const path = require("path");
const package = require("../package.json");
const child_process = require("child_process");
const process = require("process");
const os = require("os");

// 通过 Package.json 动态获取当前项目的参数
const CONETNT_REPOSITORY = package.repository.content;
const PROJECT_NAME = package.name;


// 平台框架中固定的路径
const LOCAL_CONTENT_PATH = "Content";
const LOCAL_PLUGINS_PATH = "Plugins";

// 环境变量路径
// 例：C:\Program Files\Epic Games\UE_5.5
const UE5_ROOT = process.env.UE5_5_ROOT.replace(new RegExp("\\\\", "gm"), "/");
const UNREAL_BUILD_TOOL_EXE = `${UE5_ROOT}/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe`;

// 例：C:\Program Files\Microsoft Visual Studio\2022\Community
const VS_ROOT = process.env.VS_2022_ROOT;
const MS_BUILD_EXE = `${VS_ROOT}/MSBuild/Current/Bin/amd64/MSBuild.exe`;
const MS_DEVENV_EXE = `${VS_ROOT}/Common7/IDE/devenv.exe`;


function log(...args) {
    console.log("---------------------------------------------------------------");
    console.log("--", ...args);
}

/**
 * 判断当前平台是否是windows
 * @returns
 */
function platformIsWindows() {
    return os.type() === "Windows_NT";
}

/**
 * 执行命令
 * @param {string} command 命令
 * @param {string|undefined} cwd 执行目录
 */
function exec(command, cwd) {
    console.log(`exec command on cwd: \`${cwd ?? process.cwd()}\`, command: \`${command}\``);
    child_process.execSync(command, { cwd: cwd, stdio: "inherit" });
}

/**
 * 获取工程对应uproject文件
 * @returns
 */
function getUnrealProjectFile() {
    let files = fs.readdirSync(".");
    let file = files.find((file) => file.endsWith(".uproject"));
    return path.resolve(file);
}

/**
 * 获取工程对应vs文件
 * @returns
 */
function getCppProjectFile() {
    let files = fs.readdirSync(".");
    let file = files.find((file) => file.endsWith(".sln"));
    return path.resolve(file);
}


/**
 * 执行虚幻Command
 * @param {string} commandParams
 */
function execUnrealCommand(commandParams) {
    let platform = "";
    switch (os.type()) {
        case "Windows_NT":
            platform = "Win64";
            break;
        case "Darwin":
            platform = "Mac";
            break;
        case "Linux":
            platform = "Linux";
            break;
        default:
            break;
    }

    let cmdPath = `${UE5_ROOT}/Engine/Binaries/${platform}/UnrealEditor-Cmd${platformIsWindows() ? ".exe" : ""}`;
    let projectPath = getUnrealProjectFile();
    exec(`"${cmdPath}" "${projectPath}" ${commandParams}`);
}

/**
 * 重新生成.sln文件
 */
function generateCppProject() {
    // 暂时不考虑非windows平台
    if (!platformIsWindows()) {
        return;
    }

    log("Generate C++ solution...");
    exec(`"${UNREAL_BUILD_TOOL_EXE}" -projectfiles -project="${getUnrealProjectFile()}" -game -rocket -progress`);
}

/**
 * 执行.sln文件
 */
function execCppProject() {
    // 暂时不考虑非windows平台
    if (!platformIsWindows()) {
        return;
    }

    log("Open C++ Sln File");
    exec(`"${MS_DEVENV_EXE}" "${getCppProjectFile()}"`);
}

/**
 * 更新 Content
 */
function checkoutContent() {
    if (fs.existsSync(LOCAL_CONTENT_PATH)) {
        exec(`svn update ${LOCAL_CONTENT_PATH}`);
    } else {
        fs.mkdirSync(LOCAL_CONTENT_PATH, { recursive: true });
        exec(`svn checkout ${CONETNT_REPOSITORY} ${LOCAL_CONTENT_PATH}`);
    }
}

/**
 * 切换路径到项目根目录
 */
function chdirToProjectRoot() {
    const projectRoot = path.resolve(__dirname, "../../");
    log(`switch to project root: ${projectRoot}`);
    process.chdir(projectRoot);
}

/**
 * 检查系统环境变量是否配置
 * @returns
 */
function checkEnv() {
    log("Check system environment variables...");
    if (!UE5_ROOT) {
        throw new Error("UE5_ROOT is not set, for example: export UE5_2_ROOT=C:/Program Files/Epic Games/UE_5.2");
    }

    // windows环境检查以下
    if (platformIsWindows()) {
        if (!fs.existsSync(UNREAL_BUILD_TOOL_EXE)) {
            throw new Error(`UE5_ROOT is not valid, can not find file ${UNREAL_BUILD_TOOL_EXE}`);
        }

        if (!VS_ROOT) {
            throw new Error("VS_ROOT is not set, for example: export VS_2022_ROOT=C:/Program Files/Microsoft Visual Studio/2022/Community");
        }

        if (!fs.existsSync(MS_BUILD_EXE)) {
            throw new Error(`VS_ROOT is not valid, can not find file ${MS_BUILD_EXE}`);
        }
        log(`VS_ROOT=${VS_ROOT}`);
    }

    log(`UE5_ROOT=${UE5_ROOT}`);
    log("[OK] Check system environment variables done.");
}

function installGlobalDependencies() {
    // 安装 node 全局依赖 module
    log("Install global node modules...");
    exec("npm --registry https://registry.npmmirror.com install yarn protobufjs-cli rimraf@3.0.2 -g");
}

function installPlugins() {
    // 安装 node 全局依赖 module
    log("Install global node modules...");
    // TODO 这里需要安装插件
}

/**
 * 准备脚本执行环境
 * @param {boolean} onlyChdir 只切换工作目录
 */
function prepare(onlyChdir = false) {
    log(`platform is : ${os.type()}`);
    chdirToProjectRoot();
    if (onlyChdir) return true;
    checkEnv();
    installGlobalDependencies();
    installPlugins();
}

/**
 * 重新生成虚幻C++工程并编译
 */
function generateAndBuildCppProject() {
    // 暂时不考虑非windows平台
    if (!platformIsWindows()) {
        return;
    }

    log("Generate C++ solution...");
    if (fs.existsSync(`${process.env.UE5_ENGINE_ROOT}/Setup.bat`)) {
        exec(`"${UNREAL_BUILD_TOOL_EXE}" -projectfiles -project="${getUnrealProjectFile()}" -game -engine`);
    } else {
        exec(`"${UNREAL_BUILD_TOOL_EXE}" -projectfiles -project="${getUnrealProjectFile()}" -game -rocket`);
    }

    log("Compile C++ solution...");
    exec(`"${UNREAL_BUILD_TOOL_EXE}" -Target="${PROJECT_NAME}Editor Win64 Development" -project="${getUnrealProjectFile()}"`);
    // exec(`"${MS_BUILD_EXE}" "${getCppProjectFile()}" /t:Build /p:Configuration="Development Editor" /p:Platform=Win64`);
    // exec(`"${MS_BUILD_EXE}" "${getCppProjectFile()}" /t:Build /p:Configuration="DebugGame Editor" /p:Platform=Win64`);
}


module.exports = {
    prepare,
    checkoutContent,
    generateAndBuildCppProject,
    execUnrealCommand,
    generateCppProject,
    execCppProject,
};
