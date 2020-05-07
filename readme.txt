MinND-based systems exist above the limitations of languages, platforms and tools. To work with MiND, you need the ARK into which these components integrate.

The ARK dev model focuses on safe sharing of content created by several Vendors.
Vendors produce content that you can use, they are responsible for keeping their unique naming inside. 
When you work in the ARK, you find the Vendors and "load" them into your ARK, resolve any naming conflict locally.
Of course, you are also a Vendor in your ARK.

Exceptions
 - MiND units are global; they form the common language to describe any knowledge. There is no named Vendor behind MiND, it is like the symbols you use in mathematical expressions. You can't use ARK if you don't accept MiND as the description language of your system.
 - Dust is a reference implementation of an environment that can execute a system described in the "MiND language". Of course, whatever you do in the ARK depend on Dust because it gives you the API to interact with other components in MiND. However, the Vendor of Dust is dust, and you are not locked to it.

How to get rid of Dust
 - The abstract declaration of any system only uses MiND terminology, no lock to Dust terms. If you have a better idea to run a system described in MiND, you can set up a completely different environment. Of course, in this case you can't use the ARK, it is based on Dust too. You may need it if you have a running environment beyond the Neumann Architecture.
 - In the ARK, the Dust API is a general code for each platform, if you want to change that part, you can create a new platform and you are free to create your own shared interface. Of course, that will not be binary compatible with the other platforms.
 - If you are OK with the API for a platform but would provide a better implementation of the Dust kernel, you are free to do it. The kernel is yet another module in a Dust system, you can replace it with your version, the solution is binary compatible with other modules, the interaction is provided by the platform-level common API and service codes.