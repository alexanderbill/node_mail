{
  "targets": [
    {
      "target_name": "node_tmail",
      "sources": [ "native/tmail.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
		"lib/include",
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
        'lib/lib'
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
