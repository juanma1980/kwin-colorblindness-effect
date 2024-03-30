//
// Created by matin on 20/07/22.
// Adaptded by juanma1980 27/04/24
//

#include "ColorCorrectionFilterShader.h"
#include "ColorCorrectionFilterEffect.h"
#include "ColorCorrectionFilterConfig.h"
#include <QFile>
#include <QWidget>

#if QT_VERSION_MAJOR >= 6
    #include <opengl/glutils.h>
#else
    #include <kwinglutils.h>
#endif

ColorCorrectionFilterShader::ColorCorrectionFilterShader():
        m_manager(KWin::ShaderManager::instance()),
        m_widget(new QWidget)
{
    const QString fragmentshader = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("kwin/shaders/Daltonize.frag"));
    qCritical() << fragmentshader;
    QFile file(fragmentshader);
    if (!file.open(QFile::ReadOnly))
        qCritical() << "ColorFilterCorrection: no shaders found! Exiting...";

    const QByteArray frag = file.readAll();
    auto shader = m_manager->generateShaderFromFile(KWin::ShaderTrait::MapTexture, QStringLiteral(""), fragmentshader);
    m_shader = std::move(shader);
    file.close();
    if (!m_shader->isValid())
        qCritical() << "ColorCorrectionFilter: no valid shaders found! ColorCorrectionFilter will not work.";

    m_shader_colorCorrectionFilter = m_shader->uniformLocation("colorCorrectionFilter");
    qInfo() << "ColorCorrection: shaders loaded. Option";
}

bool ColorCorrectionFilterShader::IsValid() const {
    return m_shader && m_shader->isValid();
}

const std::unique_ptr<KWin::GLShader>&
ColorCorrectionFilterShader::Bind(KWin::EffectWindow *w, qreal scale) const {
    auto frameGeometry = w->frameGeometry() * scale;
    auto expandedGeometry = w->expandedGeometry() * scale;
    auto xy = QVector2D(frameGeometry.topLeft() - expandedGeometry.topLeft());
	auto color=static_cast<int>(ColorCorrectionFilterConfig::colorCorrectionFilter());
    m_manager->pushShader(m_shader.get());
    m_shader->setUniform(m_shader_windowSize, toVector2D(frameGeometry.size()));
    m_shader->setUniform(m_shader_windowExpandedSize, toVector2D(expandedGeometry.size()));
    m_shader->setUniform(m_shader_windowTopLeft, xy);
    m_shader->setUniform(m_shader_front, 0);
    m_shader->setUniform("colorCorrectionFilter",color);
    return m_shader;
}

void ColorCorrectionFilterShader::Unbind() const {
    m_manager->popShader();
}
