package dust.mod;

public class Dust implements DustComponents {
	private static DustDialogAPI DIALOG_API = null;
	
	public static void init(DustDialogAPI api) {
		if ( (null != DIALOG_API ) && (DIALOG_API != api)) {
			DustException.throwException(null, "Multiple initialization!");
		}
		
		DIALOG_API = api;
	}
	
	public static DustDialogAPI getDialog() {
        return DIALOG_API;
    }
	
	public static <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {
		return DIALOG_API.access(cmd, tray);
	}

	DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
		return DIALOG_API.visit(visitor, tray);
	}
}
