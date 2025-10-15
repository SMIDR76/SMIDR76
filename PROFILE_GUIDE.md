# 🎨 Cyberpunk Industrial Pastel GitHub Profile Guide

## 📋 Overview

This guide explains all the features and customizations available in your new cyberpunk-themed GitHub profile README.

## 🎨 Color Palette

The profile uses a carefully selected cyberpunk industrial pastel color scheme:

| Color Name | Hex Code | Usage |
|------------|----------|-------|
| Rose Pastel Cyberpunk | `#FF6EC7` | Primary accent, titles, important badges |
| Blue Néon Pastel | `#8BE9FD` | Links, secondary highlights |
| Violet Doux | `#BD93F9` | Tertiary accents, special badges |
| Vert Menthe Néon | `#50FA7B` | Success indicators, positive stats |
| Orange Industriel | `#FFB86C` | Warning colors, special highlights |
| Jaune Pastel | `#F1FA8C` | Code highlights |
| Gris Industriel | `#6272A4` | Subtle elements |
| Background Sombre | `#282A36` | Card backgrounds |

## 🚀 Features Implemented

### 1. Animated Header
- **Waving gradient banner** with animated colors
- **Typing effect** with multiple rotating messages
- **Animated divider** GIF for visual separation
- **Neon badges** showing profile views, followers, stars, and years

### 2. About Me Section
- **ASCII art banner** with "CYBERPUNK" in block letters
- **Animated GIF** on the right side
- **TypeScript-styled** profile object
- Professional description with code syntax highlighting

### 3. Terminal Session
- **Cyberpunk-styled bash prompt** (`smidr76㉿cyberpunk`)
- **ASCII box art** for system information
- **Shell script simulation** showing profile loading
- **Blinking cursor effect** in the terminal prompt

### 4. Tech Stack & Skills
Organized into 4 categories with icon tables:
- **Programming Languages**: C, C++, Python, JavaScript, TypeScript, Bash
- **Frontend Development**: React, Next.js, Vue.js, HTML5, CSS3, Tailwind
- **Backend & Databases**: Node.js, Express, Django, PostgreSQL, MongoDB, Redis
- **DevOps & Tools**: Docker, Kubernetes, Git, GitHub, Linux, VS Code

### 5. GitHub Statistics
Multiple stat cards with custom Dracula/Cyberpunk theme:
- **GitHub Stats Card**: Contributions, PRs, Issues, Stars
- **Most Used Languages**: Language distribution chart
- **Contribution Streak**: Current and longest streak
- **Activity Graph**: Contribution timeline with custom colors
- **Trophy Achievements**: GitHub profile trophies

### 6. Featured Projects
- **Project cards** with repository pins
- **Custom styling** with neon colors
- **View Repository** buttons
- **Coming Soon** placeholder with animated GIF

### 7. Current Focus
- **Mermaid mindmap diagram** showing learning paths
- Four main branches: Low Level Programming, Web Development, DevOps, Learning Path

### 8. Connect With Me
- **Professional network badges**: GitHub, LinkedIn, Twitter, Email, Discord
- **Custom colors** for each platform
- **TypeScript-styled** collaboration object

### 9. Coding Activity
- **WakaTime integration** placeholder (requires API key setup)
- **Automated updates** via GitHub Actions

### 10. Code Philosophy
- **ASCII box art** with inspirational quote
- **Code principles** list in a styled box
- Philosophy statement about clean code

### 11. Achievements & Contributions
- **Contribution calendar** heat map
- **Snake animation** eating contribution dots
- Multiple color themes (dark/light)

### 12. Fun Zone
- **Interactive snake game** animation
- **Dev meme** of the day
- **Random dev quote** with Tokyo Night theme

### 13. Footer
- **Waving animation** at bottom
- **Visitor counter** with glitch effect
- **ASCII art logo** spelling "SMIDR76"
- **Badge collection**: Built with Love, Powered by Coffee, Makes People Smile

## ⚙️ Customization Guide

### Personal Information
Replace these placeholders in README.md:

1. **Social Media Links** (lines ~335-349):
   ```markdown
   https://linkedin.com/in/your-linkedin
   https://twitter.com/your-twitter
   mailto:your-email@example.com
   https://discord.gg/your-discord
   ```

2. **Profile Description** (lines ~65-78):
   - Update location, role, current focus
   - Modify language list
   - Change technologies
   - Update fun fact

### GitHub Secrets Setup

For automated stats updates, add these secrets to your GitHub repository:

1. **WAKATIME_API_KEY**: Get from [WakaTime](https://wakatime.com/settings/api-key)
2. **GH_TOKEN**: Personal Access Token from GitHub Settings > Developer Settings

### Workflow Configuration

Two workflows are included:

#### 1. `update-stats.yml`
- **Purpose**: Auto-update WakaTime coding statistics
- **Schedule**: Every 6 hours
- **Requires**: WAKATIME_API_KEY and GH_TOKEN secrets

#### 2. `snake-animation.yml`
- **Purpose**: Generate contribution snake animation
- **Schedule**: Daily at midnight
- **Automatic**: No secrets required
- **Output**: Creates snake SVG/GIF files

## 🔧 Advanced Customization

### Changing Colors

To change theme colors, modify these parameters in the stat cards:

```markdown
title_color=FF6EC7      # Pink
icon_color=8BE9FD       # Blue
text_color=F8F8F2       # White
bg_color=282A36         # Dark background
```

### Adding More Badges

Use [Shields.io](https://shields.io) to create custom badges:

```markdown
![Badge](https://img.shields.io/badge/Label-Value-COLOR?style=for-the-badge&logo=LOGO)
```

### Modifying Tech Stack

To add or remove technologies, edit the tables in the Tech Stack section:

```html
<td align="center" width="96">
    <img src="ICON_URL" width="65" height="65" alt="NAME" />
    <br>NAME
</td>
```

## 📊 Statistics Services Used

1. **GitHub Readme Stats**: https://github.com/anuraghazra/github-readme-stats
2. **Streak Stats**: https://github.com/DenverCoder1/github-readme-streak-stats
3. **Activity Graph**: https://github.com/Ashutosh00710/github-readme-activity-graph
4. **Trophy**: https://github.com/ryo-ma/github-profile-trophy
5. **Typing SVG**: https://github.com/DenverCoder1/readme-typing-svg
6. **Capsule Render**: https://github.com/kyechan99/capsule-render
7. **Profile Counter**: https://github.com/arturssmirnovs/github-profile-views-counter
8. **Shields.io**: https://shields.io
9. **Skill Icons**: https://skillicons.dev

## 🎯 Best Practices

1. **Update Personal Info**: Customize all placeholder text
2. **Add Real Projects**: Replace featured projects with your actual repositories
3. **Configure Workflows**: Set up GitHub secrets for automated updates
4. **Test Responsiveness**: Check appearance on mobile and desktop
5. **Regular Updates**: Keep technologies and skills current
6. **Optimize Images**: Use optimized images for faster loading
7. **Monitor Stats**: Check that stat services are working correctly

## 🐛 Troubleshooting

### Stats Not Showing?
- Verify username is correct (SMIDR76)
- Check if stat services are online
- Wait a few minutes for cache to clear

### Snake Animation Not Working?
- Ensure workflow has proper permissions
- Check if 'output' branch was created
- Verify GITHUB_TOKEN has write permissions

### Workflows Not Running?
- Enable GitHub Actions in repository settings
- Check workflow file syntax
- Add required secrets in repository settings

## 📚 Resources

- [GitHub Markdown Guide](https://guides.github.com/features/mastering-markdown/)
- [Awesome GitHub Profile README](https://github.com/abhisheknaiidu/awesome-github-profile-readme)
- [GitHub Profile README Generator](https://rahuldkjain.github.io/gh-profile-readme-generator/)

## 🎨 Design Credits

This profile uses the **Dracula Theme** color palette with cyberpunk modifications and incorporates elements from various open-source projects and services. All external services used are free and open-source friendly.

## 📝 License

Feel free to use this template for your own GitHub profile! Customize it to match your personality and style.

---

**Made with 💜 by SMIDR76**
