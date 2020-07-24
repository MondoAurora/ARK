package dust.test01.app01;

import dust.app.DustApp;
import dust.app.DustAppComponents;

public class DustAppTest01App01 implements DustAppComponents {
    public static void main(String[] args) {
        Long eJS = -1L;

        System.out.println("Hello world 3!");

        try {
            DustApp app = new DustApp();

            NativeModule m = app.addModule("dustJsonSimple.jar", "json/json-simple-1.1.1.jar");

            m.assignClass(eJS, "dust.mod.jsonsimple.JsonSimpleAgent");

            DustAgent js = app.createNative(eJS);

            js.agentProcess();
        } catch (Exception e) {
            DustException.throwException(e);
        }
    }
}
