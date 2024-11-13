# cpp101

To build:

```
╭─ywmei@ywmei-macbookpro ~/Workspace/cpp101/stage1 ‹main●› 
╰─$ bazelisk build //main:pexample
```
To run:

```
╭─ywmei@ywmei-macbookpro ~/Workspace/cpp101/stage1 ‹main●› 
╰─$ bazel-bin/main/pexample  
```

To see the exactly build command:

```
╭─ywmei@ywmei-macbookpro ~/Workspace/cpp101/stage1 ‹main●› 
╰─$ bazelisk clean; bazelisk build //main:pexample --execution_log_json_file=/tmp/bazel_log.json 

╭─ywmei@ywmei-macbookpro ~/Workspace/cpp101/stage1 ‹main●› 
╰─$ cat /tmp/bazel_log.json         
{
  "commandArgs": ["external/bazel_tools~cc_configure_extension~local_config_cc/cc_wrapper.sh", "-U_FORTIFY_SOURCE", "-fstack-protector", "-Wall", "-Wthread-safety", "-Wself-assign", "-Wunused-but-set-parameter", "-Wno-free-nonheap-object", "-fcolor-diagnostics", "-fno-omit-frame-pointer", "-std\u003dc++14", "-MD", "-MF", "bazel-out/darwin_arm64-fastbuild/bin/main/_objs/pexample/pthread_example.d", "-frandom-seed\u003dbazel-out/darwin_arm64-fastbuild/bin/main/_objs/pexample/pthread_example.o", "-iquote", ".", "-iquote", "bazel-out/darwin_arm64-fastbuild/bin", "-iquote", "external/bazel_tools", "-iquote", "bazel-out/darwin_arm64-fastbuild/bin/external/bazel_tools", "-mmacosx-version-min\u003d10.11", "-no-canonical-prefixes", "-Wno-builtin-macro-redefined", "-D__DATE__\u003d\"redacted\"", "-D__TIMESTAMP__\u003d\"redacted\"", "-D__TIME__\u003d\"redacted\"", "-c", "main/pthread_example.cc", "-o", "bazel-out/darwin_arm64-fastbuild/bin/main/_objs/pexample/pthread_example.o"],
  "environmentVariables": [{
    "name": "PATH",
    "value": "/Users/ywmei/Library/Caches/bazelisk/downloads/bazelbuild/bazel-7.4.1-darwin-arm64/bin:/Users/ywmei/google-cloud-sdk/bin:/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/usr/local/sbin:/usr/local/git/git-google/bin:/usr/local/git/current/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/opt/X11/bin:/Users/ywmei/google-cloud-sdk/bin:/Users/ywmei/.cargo/bin:/opt/homebrew/opt/fzf/bin"
  }

  ...
```