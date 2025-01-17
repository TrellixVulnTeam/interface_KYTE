#ifndef hifi_AssimpSerializer_h
#define hifi_AssimpSerializer_h

#include <hfm/HFMSerializer.h>

#include <assimp/scene.h>

class AssimpSerializer : public QObject, public HFMSerializer {
    Q_OBJECT

public:
	MediaType getMediaType() const override;
    std::unique_ptr<hfm::Serializer::Factory> getFactory() const override;

    HFMModel::Pointer read(const hifi::ByteArray& data, const hifi::VariantHash& mapping, const hifi::URL& url = hifi::URL()) override;

private:
    QUrl url;
    QString ext;

    const aiScene* scene;
    hfm::Model::Pointer hfmModel;

    QHash<QString, HFMTexture> hfmTextures;
    HFMTexture getHfmTexture(aiString path);

    void processMaterials();

    aiAnimMesh* getBlendshapeByName(QString name, aiMesh* mesh);
    void processMeshes(const hifi::VariantHash& mapping);

    QList<hfm::Shape*> getHfmShapesByMeshIndex(uint32_t meshIndex);
    void processBones();

    void processAnimations();

    void processNode(const aiNode* aiNode, int parentIndex = -1);

    void processScene(const hifi::VariantHash& mapping);

};

#endif // hifi_AssimpSerializer_h