package dust.mod;

public class Dust implements DustComponents {
	private static DustDialogAPI DIALOG_API = null;
	
	public static void init(DustDialogAPI api) {
		if ( null != DIALOG_API ) {
			DustException.throwException(null, "Multiple initialization!");
		}
		
		DIALOG_API = api;
	}
	
	public static <ValType> ValType access(DustDialogTray tray) {
		return DIALOG_API.access(tray);
	}

	DustResultType visit(Long entity, Long token, DustAgent visitor) {
		return DIALOG_API.visit(entity, token, visitor);
	}
}
