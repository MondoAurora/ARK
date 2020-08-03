package dust.test01.app01;

import dust.app.DustAppComponents;
import dust.mod.Dust;

public class OlderTests  implements DustAppComponents, AppBootTokens {

    public static void test01() throws Exception {
        DustDialogTray tray = new DustDialogTray();
        tray.setToken(JsonTypeConnector);            
        int json = Dust.access(DustDialogCmd.ADD, tray);
        
        tray.entity = json;
        tray.setToken(MiND_ModelNativeEntityContent);
        
        DustAgent js = Dust.access(DustDialogCmd.GET, tray);
        
        js.agentAction(DustAgentAction.PROCESS, null);
    }

}
