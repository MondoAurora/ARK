package dust.mod;

import dust.gen.DustGenException;

public class Dust implements DustComponents {
    private static DustDialogAPI DIALOG_API = null;
    private static DustTokenResolver TOKEN_RESOLVER = null;
    
    public interface DustDialogAPI {
        <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray);
        DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception;
    }

	
	public static <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {
		return DIALOG_API.access(cmd, tray);
	}

    public static DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
        return DIALOG_API.visit(visitor, tray);
    }
    
    public static void init(DustDialogAPI api) {
        if ( (null != DIALOG_API ) && (DIALOG_API != api)) {
            DustGenException.throwException(null, "Multiple initialization!");
        }
        
        DIALOG_API = api;
        TOKEN_RESOLVER = (DustTokenResolver) api;
    }
    
    static int getTokenEntity(DustToken token) {
        return TOKEN_RESOLVER.getTokenMember(token);
    }
}


