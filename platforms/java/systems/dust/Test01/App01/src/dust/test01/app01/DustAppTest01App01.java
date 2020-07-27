package dust.test01.app01;

import dust.app.DustApp;
import dust.app.DustAppComponents;

public class DustAppTest01App01 implements DustAppComponents {
    public static void main(String[] args) {
        int eJS = -1;

        System.out.println("Hello world 3!");

        try {
            DustApp app = new DustApp("dustRuntime.jar");

            NativeModule m;
            
//            m = app.addModule("dustRuntime.jar");
            
            m = app.addModule("dustJsonSimple.jar", "json/json-simple-1.1.1.jar");
            m.assignClass(eJS, "dust.mod.jsonsimple.JsonSimpleAgent");

            DustAgent js = app.createNative(eJS);
            
            DustDialogTray t = new DustDialogTray();

            js.agentAction(DustAgentAction.PROCESS, t);
        } catch (Exception e) {
            DustException.throwException(e);
        }
    }
}
