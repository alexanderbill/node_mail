{
  "targets": [
    {
      "target_name": "node_tmail",
      "sources": [ "native/tmail.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "D:/node/deps/uv/include",
        "D:/node/deps/curl-7.56.1/include",
        "D:/node/src",
        "D:/node/deps/openssl/openssl/include",
        "D:/node/deps/v8/include",
        "D:/TMAILSDK/source/include",
        "D:/TMAILSDK/source/tmailsdk/include",
        "D:/TMAILSDK/source/include/tlog",
        "D:/TMAILSDK/source/include/common"
      ],
      'libraries': [
        '-ltnimsdkd.lib',
        '-llibcurl_a.lib',
        '-llibcrypto.lib',
        '-llibssl.lib',
        '-llibssh2.lib',
        '-lws2_32.lib',
        '-lwldap32.lib'
      ],
      'library_dirs': [
        'lib/lib',
        'D:/TMAILSDK/platform/vs/x64/Debug'
      ],
      'configurations': {
        'Debug': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': '0',
            }
          }
        },
        'Release': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': '3',
            }
          }
        }
      }
    }
  ]
}
