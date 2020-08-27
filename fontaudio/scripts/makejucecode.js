/*
 this script generates the necessary files for including fontaudio in a juce module
 ported from AwesomeMaker from https://github.com/danlin/danlin_modules/
*/
var fs = require("fs");
var os = require("os");

const iconFilename = "./wrappers/juce/module/fontaudio/data/Icons.h";
const dataHeaderFilename =
  "./wrappers/juce/module/fontaudio/data/FontAudioData.h";
const dataSourceFilename =
  "./wrappers/juce/module/fontaudio/data/FontAudioData.cpp";

const css = fs.readFileSync("./font/fontaudio.css", "utf8");
const font = fs.readFileSync("./font/fontaudio.ttf");
if (css == "") throw "can't read fontaudio.css file!";
if (font == "") throw "can't read fontaudio.ttf file!";

const regex_icon_description = new RegExp(
  `(.fad-[^\\{]+:before )\\{([^\\}]+)\\}$`,
  "gum"
);
const regex_icon_name = new RegExp(`fad-(.+):before.+`, "um");
const regex_icon_unicode = new RegExp('.+content: "(.+)";', "um");

function camelCaseString(inputString) {
  var result = "";
  var words = inputString.split("-");
  words.forEach(function(element) {
    result += element.charAt(0).toUpperCase() + element.slice(1).toLowerCase();
  });
  return result;
}

/*
 *******************************************************************************
 ************ STEP #1: write the icons.h in the juce module FROM CSS ***********
 *******************************************************************************
 */

/*
  icons.h header
*/
fs.writeFileSync(
  iconFilename,
  "// IMPORTANT! This file is auto-generated. See ./scripts/makejucecode.js" +
    os.EOL +
    os.EOL +
    "#pragma once" +
    os.EOL +
    "namespace fontaudio" +
    os.EOL +
    "{" +
    os.EOL +
    "\ttypedef juce::String IconName;" +
    os.EOL +
    os.EOL
);

var match, iconName, iconUnicode, fileLine;
var matchesCount = 0;
while ((match = regex_icon_description.exec(css))) {
  iconName = regex_icon_name.exec(match[0]);
  iconUnicode = regex_icon_unicode.exec(match[0]);
  fileLine =
    "\tconst IconName " +
    camelCaseString(iconName[1]) +
    ' = IconName::fromUTF8(u8"\\u' +
    iconUnicode[1].slice(1) +
    '");' +
    os.EOL;

  fs.appendFileSync(iconFilename, fileLine); // TODO: this is probaly superslow - make one big string then append once
  matchesCount++;
}
console.log("icons found = " + matchesCount);

/*
  icons.h footer
*/
fs.appendFileSync(iconFilename, "} // end namespace fontaudio" + os.EOL);

/*
 *******************************************************************************
 ************ STEP #2: write the cpp/h containing the font svg data  ***********
 *******************************************************************************
 */

/*
  header file
*/
fs.writeFileSync(
  dataHeaderFilename,
  "// IMPORTANT! This file is auto-generated. See ./scripts/makejucecode.js" +
  os.EOL +
  os.EOL +
  "#pragma once" +
  os.EOL +
  "namespace FontAudioData" +
  os.EOL +
  "{" +
  os.EOL +
  "\textern const char*\tFontAudiowebfont_ttf;" +
  os.EOL +
  `\tconst int\t\t\tFontAudiowebfont_ttfSize = ${font.length};` +
    os.EOL +
    "}" +
    os.EOL +
    os.EOL
);

/*
  source file
*/
fs.writeFileSync(
  dataSourceFilename,
  "// IMPORTANT! This file is auto-generated. See ./scripts/makejucecode.js" +
    os.EOL +
    os.EOL +
    '#include "FontAudioData.h"' +
    os.EOL +
    "static const unsigned char data[] = {"
);

var dataBufferString = "";
for (var i = 0; i < font.length; i++) {
  dataBufferString += `${font[i]}`;
  if ((i + 1) % 40 == 39) dataBufferString += os.EOL;
  if (i < font.length - 1) dataBufferString += `,`;
}

fs.appendFileSync(
  dataSourceFilename,
  dataBufferString +
    "};" +
    os.EOL +
    "const char* FontAudioData::FontAudiowebfont_ttf = (const char*) data;" +
    os.EOL
);
