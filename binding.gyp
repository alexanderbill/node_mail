{
  "targets": [
    {
      "target_name": "node_tmail",
      "sources": [ "native/tmail.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "lib/include"
      ],
      'libraries': [
        '-ltnimsdkd.lib',
        '-llibcurl_a.lib',
        '-llibssh2.lib',
        '-llibcrypto.lib',
        '-llibssl.lib',
        '-lws2_32.lib',
        '-lwinmm.lib',
        '-lwldap32.lib',
        '-lmsvcrtd.lib',
      ],
      'library_dirs': [
        'lib/lib'
      ],
      'configurations': {
        'Debug': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': '3',
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
