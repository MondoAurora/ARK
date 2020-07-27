package dust.app;

import dust.mod.DustComponents;

public interface DustAppComponents extends DustComponents {
    interface NativeModule {
        Object createNative(int type);
        void assignClass(int type, String cName);
    }
    interface NativeApp {
        <RetType> RetType createNative(int type);
        NativeModule addModule(String modName, String ... libNames);
    }
}
