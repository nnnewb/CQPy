import _embed

path: bytes = _embed.cq_get_app_directory(_embed.AUTH_CODE)
path = path.decode('gb18030')
