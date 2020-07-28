package dust.app;

import dust.app.DustApp.Module;
import dust.mod.DustComponents;

public interface DustAppComponents extends DustComponents {
    interface NativeModule {
        Object createNative(int type);
        void assignClass(int type, String cName);
    }
    interface NativeApp {
        <RetType> RetType createNative(int type);
        Module addModule(String modName, int[] storeRelay, String... libNames);
        int getSystemStoreIdx(DustToken token);
    }
}
