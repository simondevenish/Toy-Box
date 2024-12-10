#include "IApp.h"
#include "IFileSystem.h"
#include "ILog.h"
#include "ITime.h"
#include "IUI.h"
#include "IProfiler.h"
#include "IScreenshot.h"
#include "ICameraController.h"
#include "IFont.h"
#include "IInput.h"
#include "IMemory.h"

// Rendering
#include "IGraphics.h"
#include "IResourceLoader.h"

// For math and other utilities
#include "Utilities/Math/MathTypes.h"
#include "Utilities/RingBuffer.h"
#include "Utilities/Threading/ThreadSystem.h"

// Animation (if needed later)
// #include "Animation/AnimatedObject.h"
// #include "Animation/Animation.h"
// #include "Animation/Clip.h"
// #include "Animation/ClipController.h"
// #include "Animation/Rig.h"
// #include "Animation/SkeletonBatcher.h"

#define D3D12_AGILITY_SDK_VERSION 715

class MyApp : public IApp
{
public:
    bool Init() override
    {
        // Initialize The Forge renderer, window, and other systems here
        RendererDesc settings = {};
        initGPUConfiguration(settings.pExtendedSettings);
        initRenderer(GetName(), &settings, &pRenderer);

        if (!pRenderer)
        {
            ShowUnsupportedMessage("Failed To Initialize renderer!");
            return false;
        }

        setupGPUConfigurationPlatformParameters(pRenderer, settings.pExtendedSettings);

        // Create a queue (command queue), and other resources as needed
        QueueDesc queueDesc = {};
        queueDesc.mType = QUEUE_TYPE_GRAPHICS;
        initQueue(pRenderer, &queueDesc, &pGraphicsQueue);

        // Initialize resource loader
        initResourceLoaderInterface(pRenderer);

        // If you want UI, fonts, profiler, etc., initialize them here as the examples do
        // For a minimal start, we skip that.

        return true;
    }

    void Exit() override
    {
        // Cleanup in reverse order of init
        exitResourceLoaderInterface(pRenderer);

        if (pGraphicsQueue)
            exitQueue(pRenderer, pGraphicsQueue);
        pGraphicsQueue = NULL;

        exitRenderer(pRenderer);
        pRenderer = NULL;
        exitGPUConfiguration();
    }

    bool Load(ReloadDesc* pReloadDesc) override
    {
        // Load resources (shaders, textures, etc.) here
        // For now, do nothing
        return true;
    }

    void Unload(ReloadDesc* pReloadDesc) override
    {
        // Unload resources here
        // For now, do nothing
    }

    void Update(float deltaTime) override
    {
        // Update your scene, camera, input, etc.
        // For now, do nothing
    }

    void Draw() override
    {
        // Acquire a swapchain image, record commands, present them
        // Minimal example: just clear screen or skip
        // Since we have not created any swapchain or pipeline, skip actual drawing
    }

    const char* GetName() override { return "ToyBoxApp"; }

private:
    Renderer* pRenderer = NULL;
    Queue* pGraphicsQueue = NULL;
};

DEFINE_APPLICATION_MAIN(MyApp)
