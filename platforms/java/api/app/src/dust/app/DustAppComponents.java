package dust.app;

import dust.app.DustApp.Module;
import dust.mod.DustComponents;

public interface DustAppComponents extends DustComponents {
    class AppTokens {
        public final DustToken typeModule;
        public final DustToken typeText;
        public final DustToken refObjects;
        public final DustToken refNative;
        
        public AppTokens(DustToken typeModule, DustToken typeText, DustToken refObjects, DustToken refNative) {
            this.typeModule = typeModule;
            this.typeText = typeText;
            this.refObjects = refObjects;
            this.refNative = refNative;
        }        
    }
    interface NativeModule {
        Object createNative(int type);
    }
    interface NativeApp {
        <RetType> RetType createNative(int type);
        Module addModule(String modName, int[] storeRelay, String... libNames);
        int getSystemStoreIdx(DustToken token);
    }
}
