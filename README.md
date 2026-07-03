# WP-Parser

Build instructions.

## Requirements

- [Git](https://git-scm.com/)
- [CMake](https://cmake.org/)
- Visual Studio (Windows) or MinGW/GCC/Clang

Check installed versions:
```
git --version
cmake --version
gcc --version
```

## Windows

```
git clone https://github.com/hxomak/wpparser.git
cd wpparser
mkdir build && cd build
```

Generate build files:
```
cmake .. -G "Visual Studio <version>"   # Visual Studio
cmake .. -G "MinGW Makefiles"           # MinGW
```

Build:
```
cmake --build . --config Release   # Visual Studio
mingw32-make                       # MinGW
```

Run:
```
Release\project.exe   # Visual Studio
project.exe           # MinGW
```

## Linux

```
git clone https://github.com/hxomak/wpparser.git
cd wpparser
mkdir build && cd build
cmake ..
make
./project
```

## Documentation

## 🌐 HTML Parser & Web Scraper
 
Fast, flexible C++ library for fetching and parsing HTML with powerful DOM querying.
 
Built with **libcurl** + **Gumbo HTML Parser**
 
---
 
## ⚡ Quick Start
 
```cpp
// Fetch HTML
CURL* handle = curl_easy_init();
std::string html = GetHtmlCode("https://example.com", handle);
 
// Parse & search
Tag root;
root.MakeRoot(html);
Tag element = FindTag(root, GUMBO_TAG_DIV, "id", "content");
std::string text = GetText(element);
```
 
---
 
## 🔍 Core Functions
 
### **Fetching**
 
| Function | Purpose |
|----------|---------|
| `GetHtmlCode(url, curl)` | Fetch HTML from URL with SSL verification & redirects |
 
### **Text Extraction**
 
| Function | Purpose |
|----------|---------|
| `GetText(tag)` | Extract all text from tag + children (normalized) |
| `GetHtmlView(tag)` | Convert tag back to HTML markup |
 
### **Searching: Exact Match**
 
| Function | Purpose |
|----------|---------|
| `FindTag()` | Find first tag by name + exact attribute |
| `FindAllTags()` | Find all tags by name + exact attribute |
 
### **Searching: Flexible Match**
 
| Function | Purpose |
|----------|---------|
| `FindTagAnyval()` | Match if attribute contains value (space-separated list) |
| `FindAllTagsAnyval()` | Find all with space-delimited attribute match |
| `FindTagAnysubval()` | Match if attribute contains substring |
| `FindAllTagsAnysubval()` | Find all with substring attribute match |
 
### **Searching: With Exclusions**
 
| Function | Purpose |
|----------|---------|
| `FindTagWithClassExc()` | Find tag, skip branches with CSS class |
| `FindTagWithTagExc()` | Find tag, skip branches with specific tag type |
 
---
 
## 🏗️ Tag Class
 
### Methods
 
```cpp
void MakeRoot(const std::string& htmlCode)
```
Parse HTML string into DOM tree. Sets root element.
 
```cpp
GumboNode* GetNode()
```
Access underlying Gumbo node for direct DOM manipulation.
 
---
 
## 📋 Examples
 
**Find div with id="main":**
```cpp
Tag main = FindTag(root, GUMBO_TAG_DIV, "id", "main");
```
 
**Get all links in document:**
```cpp
auto links = FindAllTags(root, GUMBO_TAG_A, "", "");
```
 
**Find element with class "active" (in class list):**
```cpp
Tag active = FindTagAnyval(root, GUMBO_TAG_DIV, "class", "active");
```
 
**Find tag containing "data-" in attribute:**
```cpp
Tag data = FindTagAnysubval(root, GUMBO_TAG_SPAN, "data-id", "user");
```
 
**Extract text from section (skip ads):**
```cpp
Tag content = root.__FindTagWithClassExc(root, GUMBO_TAG_DIV, "id", "content", "ad");
std::string text = GetText(content);
```
 
---
 
## ⚙️ Configuration
 
**SSL Certificate Path:** `../config/cacert.pem`  
**User-Agent:** `Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36`
 
---
 
## 🛠️ Dependencies
 
- **libcurl** — HTTP requests
- **Gumbo** — HTML5 parser
---
 
## 📝 Notes
 
- `FindTag()` returns first match; use `FindAllTags()` for all matches
- Attribute values in space-delimited lists use `AnyVal` functions
- Substring matching uses `AnySubval` functions
- All search functions traverse DOM depth-first
```

## Documentation
