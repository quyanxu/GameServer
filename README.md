# 💎 MU ALFA Season 6 — GameServer (Custom Edition)

Bienvenido al repositorio oficial del **GameServer** de [MU ALFA Season 6](https://github.com/creadormu) — un proyecto que renueva por completo la experiencia del MU clásico con **bots inteligentes**, funciones personalizadas y mejoras de calidad para servidores modernos.

> 🧠 Esta versión incluye inteligencia artificial avanzada, simulación de jugadores, mejoras en PVP y soporte completo para configuraciones por archivo.

---

## ⚔️ Características principales

✅ **Bots con IA avanzada**  
- Simulan jugadores reales: caminan, hablan, suben de nivel, dan party, hacen PVP.  
- Detectan jugadores cercanos, palabras clave y responden como humanos.  
- Usan múltiples habilidades (skills), buffs y estrategias configurables.

✅ **Configuración modular**  
- Control total de los bots desde `IA.xml` y `BotPhrases.txt` / `Answering.txt`.  
- Frases contextuales por hora, mapa, clase, cercanía, etc.  
- Sistema de respuestas por palabras clave y categorías dinámicas.

✅ **Season 6 optimizado**  
- Basado en MU 99B + Season 6 con mejoras.  
- Múltiples fixes de estabilidad y rendimiento en el GameServer.  
- Soporte para extensiones modernas de cliente y sistema de seguridad opcional.

✅ **Código limpio y expansible**  
- Organización clara por módulos.  
- Preparado para nuevas funciones sin romper compatibilidad.  
- Compatible con compiladores de Visual Studio clásicos (no requiere C++11+).

---

## 📁 Estructura del repositorio
GameServer/
├── FakeOnline.cpp/.h ← Lógica central de bots con IA
├── BotPhrases.txt ← Frases de bots por situación
├── Answering.txt ← Palabras clave + respuestas por categoría
├── IA.xml ← Configuración individual de cada bot
├── ...


> 💡 ¿Quieres que tu bot diga “¡Hola {player_name}!” cuando alguien lo saluda? Solo edita `Answering.txt`.  
> ¿Quieres que use 2 habilidades diferentes en combate? Ajusta `SkillID` y `SecondarySkillID` en `IA.xml`.

---

## 🚀 ¿Cómo empezar?

1. Compila el GameServer con Visual Studio (compatible con versiones clásicas).
2. Configura tus bots en el archivo `IA.xml`.
3. Ajusta las frases o respuestas en `BotPhrases.txt` y `Answering.txt`.
4. Ejecuta el servidor y observa cómo los bots **interactúan con los jugadores como si fueran humanos.**

---

## 📦 Proyecto completo

Este GameServer forma parte del ecosistema completo de **MU ALFA**, que incluye:

- [JoinServer](https://github.com/creadormu/JoinServer)
- [DataServer](https://github.com/creadormu/DataServer)
- [ConnectServer](https://github.com/creadormu/ConnectServer)
- [MuGuard (opcional)](https://github.com/creadormu/MuGuard) *(en desarrollo)*
- [Website + Tools (próximamente)]()

---

## 🤖 Créditos

- Desarrollado por [Ricardo Flores](https://github.com/creadormu)  
- Asistido por IA: ChatGPT (OpenAI)  
- Comunidad: Usuarios de MU en América Latina, Europa y Asia  
- Inspirado en la necesidad de **romper 20 años de estancamiento**

---

## 🌐 Comunidad

💬 Comparte, colabora y evoluciona con nosotros:  
📌 Foro: [RageZone](https://ragezone.com)  
📌 Discord: [Enlace próximamente]

---

## 🧠 “No es solo un server. Es una simulación.”  

