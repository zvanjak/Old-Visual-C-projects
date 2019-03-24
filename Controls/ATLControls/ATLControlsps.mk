
ATLControlsps.dll: dlldata.obj ATLControls_p.obj ATLControls_i.obj
	link /dll /out:ATLControlsps.dll /def:ATLControlsps.def /entry:DllMain dlldata.obj ATLControls_p.obj ATLControls_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ATLControlsps.dll
	@del ATLControlsps.lib
	@del ATLControlsps.exp
	@del dlldata.obj
	@del ATLControls_p.obj
	@del ATLControls_i.obj
