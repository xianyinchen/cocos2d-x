/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "UITest.h"
#include "CocoStudioGUITest/CocosGUIScene.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace cocostudio::timeline;

class UILoader : public TestCase
{
public:
    CREATE_FUNC(UILoader);
    UILoader()
        :TestCase()
    {
        static int testCount = 0;
        
        auto label = LabelTTF::create("load finish 0", "Marker Felt", 30);
        label->setColor(Color3B(255,0,0));
        addChild(label, 4, 4);
        label->setPosition(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/2);
        
        auto touchListener = EventListenerTouchAllAtOnce::create();
        touchListener->onTouchesEnded = CC_CALLBACK_2(UILoader::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        std::chrono::steady_clock::time_point tt = std::chrono::steady_clock::now();
        Node *rootNode = CSLoader::createNode("TestUI.csb");
        rootNode->setPosition(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/2);
        addChild(rootNode);
        rootNode->setVisible(false);
        
        int zz = 80;
        while(zz-- > 0){
            rootNode = CSLoader::createNode("TestUI.csb");
            rootNode->setPosition(VisibleRect::center().x + zz*1.2, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/2);
            addChild(rootNode);
            rootNode->setVisible(false);
        }
        
        std::chrono::steady_clock::time_point tt2 = std::chrono::steady_clock::now();
        
        long duration = static_cast<long>(std::chrono::duration_cast<std::chrono::microseconds>(tt2 - tt).count());
        auto nodeLabel = (LabelTTF*)getChildByTag(4);
        
        char tttt[256] = {0};
        sprintf(tttt, "laod finish %d", testCount);
        
        testCount = testCount + 1;
        nodeLabel->setString(tttt);
    }
    
    virtual void onEnter() override{
        TestCase::onEnter();
    }
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* /*event*/)
    {
        auto node = getChildByTag(3);
        if (node) {
            node->removeFromParent();
            TextureCache::getInstance()->removeUnusedTextures();
        }
    }
    
    virtual std::string subtitle() const override { return " "; }
};

UITests::UITests()
{
    ADD_TEST_CASE(UILoader);
}

