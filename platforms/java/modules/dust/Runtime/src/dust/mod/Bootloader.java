package dust.mod;

import dust.app.DustAppComponents.NativeApp;
import dust.mod.runtime.RuntimeAgent;

public class Bootloader {
    
    public static void bootRuntime(NativeApp app) {
        RuntimeAgent.createRuntime(app);
    }

}
