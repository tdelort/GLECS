target_sources(${PROJECT_NAME}
    PRIVATE
        "Entity.cpp"
        "Component.cpp"

        "components/Transform.cpp"
        "components/MeshRenderer.cpp"

        "assets/Mesh.cpp"
        "assets/ObjMesh.cpp"
        "assets/Shader.cpp"
        "assets/Material.cpp"

        "FileUtility.cpp"
)