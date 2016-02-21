//
//  BoardLayer.cpp
//  Dijkstra
//
//  Created by saichi on 2016/02/21.
//
//

#include "BoardLayer.hpp"
#include "NodeLayer.hpp"

USING_NS_CC;
using namespace std;

bool BoardLayer::init(){
    if(!Layer::init()){
        return false;
    }
    winSize = Director::getInstance()->getVisibleSize();
    return true;
}

void BoardLayer::createBoard(int x, int y){
    // ボード(背景)作成
    auto bg = LayerColor::create(Color4B::BLACK, winSize.width, (winSize.width/x)*y);
    this->addChild(bg);
    // ノード(マス)作成
    createNode(x, y);
    setNeighborNode(x, y);
}
void BoardLayer::createNode(int x, int y){
    log("%d * %d マスで生成します", x, y);
    int id = 0;
    for (int i=0; i<x; i++){
        for (int j=0; j<y; j++){
            auto nl = NodeLayer::create();
            nl->setId(id);
            nl->setContentSize(Size((winSize.width/x)-3,(winSize.width/x)-3));
            nl->setKind(2);
            nl->setPosition(Vec2((winSize.width/x)*i, (winSize.width/x)*j));
            this->addChild(nl);
            allNode.pushBack(nl);
            id ++;
        }
    }
}
void BoardLayer::setNeighborNode(int x, int y) {
    
    for (auto node: allNode) {
        int selfId = node->getId();
        // up neighbor
        if ((selfId + 1) % y != 0) {
            auto tNode = allNode.at(selfId + 1);
            node->addNeighborNode(tNode);
        }
        // down neighbor
        if (selfId % y != 0) {
            auto tNode = allNode.at(selfId - 1);
            node->addNeighborNode(tNode);
        }
        // left neighbor
        if (selfId - y >= 0) {
            auto tNode = allNode.at(selfId - y);
            node->addNeighborNode(tNode);
        }
        // right neighbor
        if (selfId + y < x * y) {
            auto tNode = allNode.at(selfId + y);
            node->addNeighborNode(tNode);
        }
    }
}
void BoardLayer::searchRoute(int id){
    log("search %d", id);
    Vector<NodeLayer*> neighborNode = allNode.at(id)->getNeighborNode();
    for (auto nn: neighborNode) {
        log("nid:%d",nn->getId());
    }
}