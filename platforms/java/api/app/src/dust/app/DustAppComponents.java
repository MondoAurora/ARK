package dust.app;

import dust.mod.DustComponents;

public interface DustAppComponents extends DustComponents {
	interface NativeApp {
	    Object createNative(Long type);
	}
}
