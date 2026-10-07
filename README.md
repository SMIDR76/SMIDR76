"""Generates the SVG assets for the GitHub profile README.
Run: python gen.py  (writes into ../assets)
"""
import math, os, random

OUT = os.path.join(os.path.dirname(__file__), "..", "assets")
os.makedirs(OUT, exist_ok=True)

BG = "#0b0d10"
PANEL = "#0f1216"
LINE = "#1d232a"
LINE2 = "#2b323b"
MUTED = "#7d8590"
TEXT = "#e6e8eb"
ACC = "#e8a33d"
SANS = "'Segoe UI','Helvetica Neue',Helvetica,Arial,sans-serif"
MONO = "'JetBrains Mono','Cascadia Mono',Consolas,'SF Mono',Menlo,monospace"


def save(name, body, w, h, label):
    svg = (f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {w} {h}" '
           f'width="{w}" height="{h}" role="img" aria-label="{label}">\n{body}\n</svg>\n')
    with open(os.path.join(OUT, name), "w", encoding="utf-8") as f:
        f.write(svg)


def frame(w, h):
    return (f'<rect width="{w}" height="{h}" rx="14" fill="{BG}"/>'
            f'<rect x="0.5" y="0.5" width="{w-1}" height="{h-1}" rx="14" fill="none" stroke="{LINE}"/>')


def grid(w, h, step=40, color="#12161b", clip="r"):
    return (f'<defs><pattern id="g{step}" width="{step}" height="{step}" patternUnits="userSpaceOnUse">'
            f'<path d="M{step} 0H0V{step}" fill="none" stroke="{color}" stroke-width="1"/></pattern>'
            f'<clipPath id="{clip}"><rect width="{w}" height="{h}" rx="14"/></clipPath></defs>'
            f'<rect width="{w}" height="{h}" fill="url(#g{step})" clip-path="url(#{clip})"/>')


def blob(cx, cy, r, seed, n=9, jitter=0.22):
    rnd = random.Random(seed)
    pts = []
    for i in range(n):
        a = 2 * math.pi * i / n
        rr = r * (1 + rnd.uniform(-jitter, jitter))
        pts.append((cx + rr * math.cos(a), cy + rr * 0.72 * math.sin(a)))
    # Catmull-Rom -> cubic bezier, closed
    d = f"M{pts[0][0]:.1f},{pts[0][1]:.1f}"
    for i in range(n):
        p0, p1, p2, p3 = pts[i - 1], pts[i], pts[(i + 1) % n], pts[(i + 2) % n]
        c1 = (p1[0] + (p2[0] - p0[0]) / 6, p1[1] + (p2[1] - p0[1]) / 6)
        c2 = (p2[0] - (p3[0] - p1[0]) / 6, p2[1] - (p3[1] - p1[1]) / 6)
        d += f"C{c1[0]:.1f},{c1[1]:.1f} {c2[0]:.1f},{c2[1]:.1f} {p2[0]:.1f},{p2[1]:.1f}"
    return d + "Z"


def contours(cx, cy, rmax, count, seed, color):
    out = []
    for k in range(count):
        r = rmax * (1 - k / count)
        op = 0.35 + 0.65 * (k / count)
        out.append(f'<path d="{blob(cx, cy, r, seed + k * 7)}" fill="none" stroke="{color}" '
                   f'stroke-width="1.2" opacity="{op:.2f}"/>')
    return "".join(out)


# ---------------------------------------------------------------- HEADER
def header():
    W, H = 1600, 520
    b = [frame(W, H), grid(W, H)]
    b.append(f'<g clip-path="url(#r)">')
    b.append(contours(1210, 300, 520, 11, 3, "#1a2027"))
    b.append(contours(380, 560, 300, 6, 41, "#151a20"))
    b.append('</g>')

    # top-down level layout (right side)
    ox, oy = 880, 92
    L = []
    rooms = [(0, 120, 150, 110), (210, 40, 190, 150), (210, 250, 120, 120),
             (460, 70, 170, 230), (390, 330, 240, 60)]
    for x, y, w, h in rooms:
        L.append(f'<rect x="{ox+x}" y="{oy+y}" width="{w}" height="{h}" fill="{PANEL}" '
                 f'stroke="{LINE2}" stroke-width="2"/>')
    corridors = [(150, 160, 60, 30), (400, 100, 60, 30), (260, 190, 30, 60), (330, 335, 60, 30),
                 (520, 300, 40, 30)]
    for x, y, w, h in corridors:
        L.append(f'<rect x="{ox+x}" y="{oy+y}" width="{w}" height="{h}" fill="{PANEL}"/>')
    # cover blocks
    for x, y, w, h in [(250, 80, 40, 14), (330, 130, 14, 36), (500, 160, 50, 14),
                       (560, 220, 14, 40), (250, 300, 36, 12)]:
        L.append(f'<rect x="{ox+x}" y="{oy+y}" width="{w}" height="{h}" fill="{LINE2}"/>')
    # sightline cone from spawn to landmark
    L.append(f'<defs><linearGradient id="cone" x1="0" x2="1"><stop offset="0" stop-color="{ACC}" '
             f'stop-opacity="0.28"/><stop offset="1" stop-color="{ACC}" stop-opacity="0"/></linearGradient></defs>')
    sx, sy = ox + 60, oy + 175
    L.append(f'<path d="M{sx},{sy} L{ox+600},{oy+95} L{ox+600},{oy+175} Z" fill="url(#cone)"/>')
    # landmark
    lx, ly = ox + 585, oy + 130
    L.append(f'<path d="M{lx},{ly-22} L{lx+19},{ly+12} L{lx-19},{ly+12} Z" fill="none" stroke="{ACC}" stroke-width="2"/>')
    L.append(f'<text x="{lx}" y="{ly+36}" fill="{ACC}" font-family="{MONO}" font-size="13" '
             f'text-anchor="middle" letter-spacing="2">LANDMARK</text>')
    # critical path
    path = [(sx, sy), (ox + 180, oy + 175), (ox + 275, oy + 175), (ox + 275, oy + 115),
            (ox + 430, oy + 115), (ox + 505, oy + 115), (ox + 505, oy + 250), (ox + 540, oy + 315),
            (ox + 540, oy + 360), (ox + 430, oy + 360), (ox + 300, oy + 350)]
    pd = "M" + " L".join(f"{x},{y}" for x, y in path)
    L.append(f'<path d="{pd}" fill="none" stroke="{ACC}" stroke-width="2.5" stroke-dasharray="10 9" '
             f'stroke-linecap="round" stroke-linejoin="round">'
             f'<animate attributeName="stroke-dashoffset" from="190" to="0" dur="4s" repeatCount="indefinite"/></path>')
    beats = [(sx, sy, "01"), (ox + 275, oy + 150, "02"), (ox + 470, oy + 115, "03"),
             (ox + 540, oy + 335, "04"), (ox + 300, oy + 350, "05")]
    for x, y, t in beats:
        L.append(f'<circle cx="{x}" cy="{y}" r="15" fill="{BG}" stroke="{ACC}" stroke-width="2"/>'
                 f'<text x="{x}" y="{y+4.5}" fill="{ACC}" font-family="{MONO}" font-size="12" '
                 f'font-weight="700" text-anchor="middle">{t}</text>')
    labels = [(ox + 75, oy + 252, "SPAWN"), (ox + 305, oy + 30, "COMBAT A"),
              (ox + 545, oy + 60, "VISTA"), (ox + 445, oy + 412, "OBJECTIVE")]
    for x, y, t in labels:
        L.append(f'<text x="{x}" y="{y}" fill="{MUTED}" font-family="{MONO}" font-size="12" '
                 f'text-anchor="middle" letter-spacing="2">{t}</text>')
    b += L

    # left typography
    b.append(f'<text x="80" y="92" fill="{MUTED}" font-family="{MONO}" font-size="15" letter-spacing="4">'
             f'LD-DOC  /  REV.07  /  LE HAVRE, FR</text>')
    b.append(f'<text x="74" y="250" fill="{TEXT}" font-family="{SANS}" font-size="118" font-weight="700" '
             f'letter-spacing="-2">Cenk K.</text>')
    b.append(f'<rect x="80" y="282" width="64" height="4" fill="{ACC}"/>')
    b.append(f'<text x="80" y="336" fill="{TEXT}" font-family="{SANS}" font-size="32" font-weight="400">'
             f'Level Designer &amp; Environment Artist</text>')
    b.append(f'<text x="80" y="378" fill="{MUTED}" font-family="{SANS}" font-size="20">'
             f'Playable spaces in Unreal Engine 5, from paper to final light.</text>')

    # scale bar + north arrow
    y = 456
    b.append(f'<g font-family="{MONO}" font-size="12" fill="{MUTED}">'
             f'<path d="M80 {y}h240M80 {y-6}v12M200 {y-4}v8M320 {y-6}v12" stroke="{MUTED}" stroke-width="1.5"/>'
             f'<rect x="80" y="{y-3}" width="120" height="6" fill="{MUTED}"/>'
             f'<text x="80" y="{y+26}">0</text><text x="200" y="{y+26}" text-anchor="middle">10</text>'
             f'<text x="320" y="{y+26}" text-anchor="end">20 m</text>'
             f'<text x="360" y="{y+5}" letter-spacing="2">SCALE 1:1</text></g>')
    nx, ny = 1520, 455
    b.append(f'<g><circle cx="{nx}" cy="{ny}" r="24" fill="none" stroke="{LINE2}" stroke-width="1.5"/>'
             f'<path d="M{nx},{ny-18} L{nx+8},{ny+10} L{nx},{ny+4} L{nx-8},{ny+10} Z" fill="{MUTED}"/>'
             f'<text x="{nx}" y="{ny-32}" fill="{MUTED}" font-family="{MONO}" font-size="12" '
             f'text-anchor="middle">N</text></g>')
    save("header.svg", "".join(b), W, H, "Cenk K. Level Designer and Environment Artist")


# ---------------------------------------------------------------- SECTION TITLES
def section(name, idx, title, W=1600, H=96):
    b = [f'<text x="2" y="58" fill="{ACC}" font-family="{MONO}" font-size="20" font-weight="700">{idx}</text>',
         f'<text x="62" y="58" fill="{TEXT}" font-family="{SANS}" font-size="30" font-weight="600" '
         f'letter-spacing="6">{title}</text>']
    tw = 62 + len(title) * 25 + 40
    b.append(f'<path d="M{tw} 50H{W-2}" stroke="{LINE2}" stroke-width="1.5"/>'
             f'<path d="M{W-2} 42v16" stroke="{LINE2}" stroke-width="1.5"/>')
    save(name, "".join(b), W, H, title.title())


# ---------------------------------------------------------------- PIPELINE (isometric)
S = 19  # px per metre-unit


def iso(x, y, z, ox, oy):
    return (ox + (x - y) * S * 0.866, oy + (x + y) * S * 0.5 - z * S)


def pts(ps):
    return " ".join(f"{x:.1f},{y:.1f}" for x, y in ps)


BOXES = [  # x0, y0, x1, y1, h, kind
    (1.0, 1.0, 4.6, 3.8, 3.0, "house"),
    (6.6, 0.8, 8.0, 2.2, 7.5, "tower"),
    (0.8, 5.0, 1.4, 9.0, 1.6, "wall"),
    (3.6, 6.2, 5.6, 6.8, 0.9, "cover"),
    (6.6, 4.8, 7.2, 6.8, 0.9, "cover"),
]
TREES = [(9.0, 4.0, 3.2), (2.6, 9.4, 2.6), (9.3, 7.6, 2.9), (5.2, 0.6, 2.4), (0.4, 4.0, 2.2)]
ROCKS = [(8.2, 9.2), (5.0, 8.6), (2.2, 4.6)]
PATH = [(9.6, 9.6), (6.0, 8.0), (5.4, 5.4), (7.3, 3.8), (7.3, 2.6)]


def shade(hexc, f):
    c = [int(hexc[i:i + 2], 16) for i in (1, 3, 5)]
    c = [max(0, min(255, int(v * f))) for v in c]
    return "#%02x%02x%02x" % tuple(c)


def mix(a, b, t):
    ca = [int(a[i:i + 2], 16) for i in (1, 3, 5)]
    cb = [int(b[i:i + 2], 16) for i in (1, 3, 5)]
    return "#%02x%02x%02x" % tuple(int(ca[k] + (cb[k] - ca[k]) * t) for k in range(3))


def hull(points):
    points = sorted(set(points))
    if len(points) <= 2:
        return points
    def cross(o, a, b):
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])
    lo, up = [], []
    for p in points:
        while len(lo) >= 2 and cross(lo[-2], lo[-1], p) <= 0:
            lo.pop()
        lo.append(p)
    for p in reversed(points):
        while len(up) >= 2 and cross(up[-2], up[-1], p) <= 0:
            up.pop()
        up.append(p)
    return lo[:-1] + up[:-1]


def box_faces(bx, ox, oy, top, left, right, stroke=None, sw=1):
    x0, y0, x1, y1, h, _ = bx
    P = lambda x, y, z: iso(x, y, z, ox, oy)
    st = f' stroke="{stroke}" stroke-width="{sw}" stroke-linejoin="round"' if stroke else ""
    f_r = [P(x1, y0, 0), P(x1, y1, 0), P(x1, y1, h), P(x1, y0, h)]   # +x face
    f_l = [P(x0, y1, 0), P(x1, y1, 0), P(x1, y1, h), P(x0, y1, h)]   # +y face
    f_t = [P(x0, y0, h), P(x1, y0, h), P(x1, y1, h), P(x0, y1, h)]
    return (f'<polygon points="{pts(f_r)}" fill="{right}"{st}/>'
            f'<polygon points="{pts(f_l)}" fill="{left}"{st}/>'
            f'<polygon points="{pts(f_t)}" fill="{top}"{st}/>')


def roof(bx, ox, oy, c_l, c_r):
    x0, y0, x1, y1, h, _ = bx
    P = lambda x, y, z: iso(x, y, z, ox, oy)
    ym, rh = (y0 + y1) / 2, 1.5
    left_slope = [P(x0, y1, h), P(x1, y1, h), P(x1, ym, h + rh), P(x0, ym, h + rh)]
    right_gable = [P(x1, y0, h), P(x1, y1, h), P(x1, ym, h + rh)]
    back_slope = [P(x0, y0, h), P(x1, y0, h), P(x1, ym, h + rh), P(x0, ym, h + rh)]
    return (f'<polygon points="{pts(back_slope)}" fill="{shade(c_l, 0.8)}"/>'
            f'<polygon points="{pts(left_slope)}" fill="{c_l}"/>'
            f'<polygon points="{pts(right_gable)}" fill="{c_r}"/>')


def tree(t, ox, oy, canopy, trunk, lit=None):
    x, y, hgt = t
    bx, by = iso(x, y, 0, ox, oy)
    tx, ty = iso(x, y, hgt, ox, oy)
    o = f'<path d="M{bx:.1f},{by:.1f} L{tx:.1f},{ty+10:.1f}" stroke="{trunk}" stroke-width="4"/>'
    for dx, dy, r, f in [(0, 0, 22, 1.0), (-11, 9, 15, 0.85), (12, 7, 16, 0.92), (2, -14, 15, 1.08)]:
        o += f'<circle cx="{tx+dx:.1f}" cy="{ty+dy:.1f}" r="{r}" fill="{shade(canopy, f)}"/>'
    if lit:
        o += f'<circle cx="{tx-8:.1f}" cy="{ty-6:.1f}" r="12" fill="{lit}" opacity="0.55"/>'
    return o


def rock(r, ox, oy, c, lit=None):
    x, y = r
    cx, cy = iso(x, y, 0, ox, oy)
    p = [(cx - 16, cy), (cx - 10, cy - 13), (cx + 3, cy - 17), (cx + 15, cy - 7), (cx + 14, cy + 3), (cx - 2, cy + 6)]
    o = f'<polygon points="{pts(p)}" fill="{c}"/>'
    o += f'<polygon points="{pts([(cx-10,cy-13),(cx+3,cy-17),(cx+15,cy-7),(cx+1,cy-6)])}" fill="{lit or shade(c,1.3)}"/>'
    return o


def ground(ox, oy, fill, stroke=None):
    g = [iso(0, 0, 0, ox, oy), iso(10, 0, 0, ox, oy), iso(10, 10, 0, ox, oy), iso(0, 10, 0, ox, oy)]
    st = f' stroke="{stroke}" stroke-width="1.5"' if stroke else ""
    return f'<polygon points="{pts(g)}" fill="{fill}"{st}/>'


def ground_grid(ox, oy, c):
    o = ""
    for i in range(1, 10):
        a, b2 = iso(i, 0, 0, ox, oy), iso(i, 10, 0, ox, oy)
        c2, d = iso(0, i, 0, ox, oy), iso(10, i, 0, ox, oy)
        o += f'<path d="M{a[0]:.1f},{a[1]:.1f}L{b2[0]:.1f},{b2[1]:.1f}M{c2[0]:.1f},{c2[1]:.1f}L{d[0]:.1f},{d[1]:.1f}" stroke="{c}" stroke-width="1"/>'
    return o


def path_line(ox, oy, color, width=2.5, dash="8 7", anim=False):
    d = "M" + " L".join(f"{iso(x, y, 0, ox, oy)[0]:.1f},{iso(x, y, 0, ox, oy)[1]:.1f}" for x, y in PATH)
    a = ('<animate attributeName="stroke-dashoffset" from="150" to="0" dur="4s" repeatCount="indefinite"/>'
         if anim else "")
    return (f'<path d="{d}" fill="none" stroke="{color}" stroke-width="{width}" stroke-dasharray="{dash}" '
            f'stroke-linecap="round" stroke-linejoin="round">{a}</path>')


def sorted_items():
    items = [("box", b, (b[0] + b[2]) / 2 + (b[1] + b[3]) / 2) for b in BOXES]
    items += [("tree", t, t[0] + t[1]) for t in TREES]
    items += [("rock", r, r[0] + r[1]) for r in ROCKS]
    return sorted(items, key=lambda i: i[2])


def pipeline():
    W, H = 1600, 640
    PW, PH, GAP, M = 350, 500, 40, 40
    b = [frame(W, H)]
    stages = [
        ("01", "LAYOUT", ["Intent, flow, beats", "and sightlines on paper"]),
        ("02", "BLOCKOUT", ["Greybox at 1:1 metrics,", "playtest, iterate"]),
        ("03", "ART PASS", ["Modular kits, foliage,", "set dressing, storytelling"]),
        ("04", "LIGHTING", ["Mood, readability,", "Lumen, fog, post-process"]),
    ]
    for i, (n, name, caption) in enumerate(stages):
        px, py = M + i * (PW + GAP), 40
        ox, oy = px + PW / 2, py + 175
        b.append(f'<rect x="{px}" y="{py}" width="{PW}" height="{PH}" rx="10" fill="{PANEL}" stroke="{LINE}"/>')
        b.append(f'<clipPath id="p{i}"><rect x="{px}" y="{py}" width="{PW}" height="{PH}" rx="10"/></clipPath>')
        b.append(f'<g clip-path="url(#p{i})">')
        if i == 0:
            b.append(ground(ox, oy, "none", LINE2))
            b.append(ground_grid(ox, oy, "#171c22"))
            for bx in BOXES:
                x0, y0, x1, y1 = bx[:4]
                fp = [iso(x0, y0, 0, ox, oy), iso(x1, y0, 0, ox, oy), iso(x1, y1, 0, ox, oy), iso(x0, y1, 0, ox, oy)]
                b.append(f'<polygon points="{pts(fp)}" fill="none" stroke="{MUTED}" stroke-width="1.5" stroke-dasharray="4 4"/>')
            for t in TREES:
                cx, cy = iso(t[0], t[1], 0, ox, oy)
                b.append(f'<circle cx="{cx:.1f}" cy="{cy:.1f}" r="6" fill="none" stroke="{MUTED}" stroke-width="1.2"/>')
            # sightline
            s = iso(*PATH[0], 0, ox, oy)
            l1, l2 = iso(6.0, 0.2, 0, ox, oy), iso(8.6, 2.6, 0, ox, oy)
            b.append(f'<polygon points="{pts([s, l1, l2])}" fill="{ACC}" opacity="0.10"/>')
            b.append(path_line(ox, oy, ACC, anim=True))
            for k, (x, y) in enumerate(PATH):
                cx, cy = iso(x, y, 0, ox, oy)
                b.append(f'<circle cx="{cx:.1f}" cy="{cy:.1f}" r="9" fill="{PANEL}" stroke="{ACC}" stroke-width="1.6"/>'
                         f'<text x="{cx:.1f}" y="{cy+3.5:.1f}" fill="{ACC}" font-family="{MONO}" font-size="9" '
                         f'font-weight="700" text-anchor="middle">{k+1}</text>')
        elif i == 1:
            b.append(ground(ox, oy, "#14181d", LINE2))
            b.append(ground_grid(ox, oy, "#1d232a"))
            b.append(path_line(ox, oy, "#4a525c", 2, "6 6"))
            for kind, it, _ in sorted_items():
                if kind == "box":
                    b.append(box_faces(it, ox, oy, "#9aa1a9", "#5d646c", "#757c84"))
                    if it[5] == "tower":
                        b.append(box_faces((it[0] + 0.3, it[1] + 0.3, it[2] - 0.3, it[3] - 0.3, it[4] + 1.2, ""),
                                           ox, oy, ACC, shade(ACC, 0.55), shade(ACC, 0.75)))
            # player capsule for scale
            cx, cy = iso(7.8, 8.8, 0, ox, oy)
            b.append(f'<rect x="{cx-5:.1f}" y="{cy-34:.1f}" width="10" height="34" rx="5" fill="{ACC}"/>')
            b.append(f'<text x="{cx+12:.1f}" y="{cy-22:.1f}" fill="{MUTED}" font-family="{MONO}" font-size="10">1.8 m</text>')
        else:
            lit = i == 3
            grd = "#1a2119" if not lit else "#2a2416"
            b.append(ground(ox, oy, grd))
            if lit:
                # long warm shadows, light from the left/back
                L = (1.15, -0.55)
                for bx in BOXES:
                    x0, y0, x1, y1, h, _ = bx
                    base = [(x0, y0), (x1, y0), (x1, y1), (x0, y1)]
                    if bx[5] == "house":
                        h += 1.5
                    proj = [(x + L[0] * h, y + L[1] * h) for x, y in base]
                    hl = hull(base + proj)
                    hl = [iso(min(max(x, 0), 10), min(max(y, 0), 10), 0, ox, oy) for x, y in hl]
                    b.append(f'<polygon points="{pts(hl)}" fill="#0d0b07" opacity="0.6"/>')
                for t in TREES:
                    x, y, hgt = t
                    a = iso(x, y, 0, ox, oy)
                    e = iso(min(x + L[0] * hgt, 10), max(y + L[1] * hgt, 0), 0, ox, oy)
                    b.append(f'<path d="M{a[0]:.1f},{a[1]:.1f}L{e[0]:.1f},{e[1]:.1f}" stroke="#0d0b07" '
                             f'stroke-width="16" stroke-linecap="round" opacity="0.55"/>')
            for kind, it, _ in sorted_items():
                if kind == "box":
                    k = it[5]
                    if k == "house":
                        top, l, r = ("#8a7d6b", "#5f564a", "#4a433a") if not lit else ("#d9a865", "#7a5d3b", "#3d2f20")
                        b.append(box_faces(it, ox, oy, top, l, r))
                        rl, rr = ("#6b3f32", "#4d2e25") if not lit else ("#b8653f", "#4a2a1d")
                        b.append(roof(it, ox, oy, rl, rr))
                        # windows
                        for wy in (1.6, 3.0):
                            q = [iso(4.6, wy, 1.2, ox, oy), iso(4.6, wy + 0.6, 1.2, ox, oy),
                                 iso(4.6, wy + 0.6, 2.0, ox, oy), iso(4.6, wy, 2.0, ox, oy)]
                            b.append(f'<polygon points="{pts(q)}" fill="{"#2a2620" if not lit else "#ffcf7a"}"/>')
                    elif k == "tower":
                        top, l, r = ("#7a7f86", "#4f545a", "#3d4146") if not lit else ("#e0b072", "#80613e", "#3b3026")
                        b.append(box_faces(it, ox, oy, top, l, r))
                        cap = (it[0] - 0.25, it[1] - 0.25, it[2] + 0.25, it[3] + 0.25, it[4] + 0.6, "")
                        capb = (cap[0], cap[1], cap[2], cap[3], it[4], "")
                        b.append(box_faces(cap, ox, oy, top, shade(l, 0.9), shade(r, 0.9)))
                        if lit:
                            fx, fy = iso((it[0] + it[2]) / 2, (it[1] + it[3]) / 2, it[4] + 1.6, ox, oy)
                            b.append(f'<circle cx="{fx:.1f}" cy="{fy:.1f}" r="16" fill="{ACC}" opacity="0.25"/>'
                                     f'<circle cx="{fx:.1f}" cy="{fy:.1f}" r="5" fill="#ffd28a"/>')
                    else:
                        top, l, r = ("#6e655a", "#4d463e", "#3c3630") if not lit else ("#c9995c", "#6a5034", "#33281c")
                        b.append(box_faces(it, ox, oy, top, l, r))
                elif kind == "tree":
                    b.append(tree(it, ox, oy, "#2f4a2c" if not lit else "#4b5a24",
                                  "#3b2e22", "#d9a441" if lit else None))
                else:
                    b.append(rock(it, ox, oy, "#4a4a46" if not lit else "#4a3f30",
                                  "#b98b52" if lit else None))
            if lit:
                b.append(f'<defs><radialGradient id="sun" cx="0.05" cy="0.15" r="0.9">'
                         f'<stop offset="0" stop-color="{ACC}" stop-opacity="0.35"/>'
                         f'<stop offset="1" stop-color="{ACC}" stop-opacity="0"/></radialGradient>'
                         f'<linearGradient id="fog" x1="0" y1="0" x2="0" y2="1">'
                         f'<stop offset="0.55" stop-color="#e8a33d" stop-opacity="0"/>'
                         f'<stop offset="1" stop-color="#e8a33d" stop-opacity="0.10"/></linearGradient></defs>')
                b.append(f'<rect x="{px}" y="{py}" width="{PW}" height="{PH}" fill="url(#sun)"/>')
                b.append(f'<rect x="{px}" y="{py}" width="{PW}" height="{PH}" fill="url(#fog)"/>')
        b.append('</g>')
        # labels
        b.append(f'<text x="{px+22}" y="{py+40}" fill="{ACC}" font-family="{MONO}" font-size="15" font-weight="700">{n}</text>'
                 f'<text x="{px+56}" y="{py+40}" fill="{TEXT}" font-family="{SANS}" font-size="17" font-weight="600" '
                 f'letter-spacing="4">{name}</text>')
        b.append(f'<path d="M{px+22} {py+PH-92}h{PW-44}" stroke="{LINE}"/>')
        for k, c in enumerate(caption):
            b.append(f'<text x="{px+22}" y="{py+PH-60+k*24}" fill="{MUTED}" font-family="{SANS}" font-size="16">{c}</text>')
        if i < 3:
            ax = px + PW + GAP / 2
            b.append(f'<path d="M{ax-7} {py+PH/2-8} l8 8 l-8 8" fill="none" stroke="{MUTED}" stroke-width="2"/>')
    b.append(f'<text x="{W/2}" y="{H-36}" fill="{MUTED}" font-family="{MONO}" font-size="13" letter-spacing="3" '
             f'text-anchor="middle">SAME SPACE, FOUR PASSES. I OWN THE WHOLE CHAIN.</text>')
    save("pipeline.svg", "".join(b), W, H, "Pipeline: layout, blockout, art pass, lighting")


# ---------------------------------------------------------------- DISCIPLINES
def disciplines():
    W, H = 1600, 700
    b = [frame(W, H)]
    cols = [
        ("LEVEL DESIGN", "Make it play", [
            ("Paper design", "intent docs, top-down maps, beat charts"),
            ("Blockout", "greybox at 1:1, player metrics, cover heights"),
            ("Flow & pacing", "critical path, loops, tension and release"),
            ("Guidance", "landmarks, sightlines, light and color as signposts"),
            ("Combat spaces", "cover logic, flanks, verticality, sightline control"),
            ("Scripting", "Blueprints, triggers, gameplay events"),
        ]),
        ("ENVIRONMENT ART", "Make it believable", [
            ("Worldbuilding", "environmental storytelling, decay, history"),
            ("Terrain", "landscape sculpting, Gaea, layered materials"),
            ("Set dressing", "modular kits, Megascans, composition"),
            ("Foliage & PCG", "scattering, Dash, procedural rules"),
            ("Lighting", "Lumen, volumetric fog, post-process, mood"),
            ("Optimization", "Nanite, HLOD, World Partition, profiling"),
        ]),
    ]
    for c, (title, sub, items) in enumerate(cols):
        x = 80 + c * 760
        b.append(f'<text x="{x}" y="96" fill="{TEXT}" font-family="{SANS}" font-size="26" font-weight="600" '
                 f'letter-spacing="5">{title}</text>')
        b.append(f'<text x="{x}" y="128" fill="{ACC}" font-family="{MONO}" font-size="15" letter-spacing="2">'
                 f'// {sub.upper()}</text>')
        for k, (h, d) in enumerate(items):
            y = 190 + k * 66
            b.append(f'<path d="M{x} {y-30}h660" stroke="{LINE}"/>')
            b.append(f'<text x="{x}" y="{y}" fill="{MUTED}" font-family="{MONO}" font-size="14">{k+1:02d}</text>'
                     f'<text x="{x+50}" y="{y}" fill="{TEXT}" font-family="{SANS}" font-size="20" font-weight="600">{h.replace("&","&amp;")}</text>'
                     f'<text x="{x+50}" y="{y+24}" fill="{MUTED}" font-family="{SANS}" font-size="16">{d}</text>')
    b.append(f'<path d="M800 70V570" stroke="{LINE}"/>')
    # toolset strip
    y = 615
    b.append(f'<path d="M0.5 {y-40}H{W-0.5}" stroke="{LINE}"/>')
    b.append(f'<text x="80" y="{y+8}" fill="{ACC}" font-family="{MONO}" font-size="14" letter-spacing="3">TOOLSET</text>')
    tools = ["Unreal Engine 5", "Blender", "Substance 3D", "Gaea", "Megascans", "SpeedTree", "Photoshop", "Dash"]
    b.append(f'<text x="210" y="{y+8}" fill="{TEXT}" font-family="{MONO}" font-size="16" letter-spacing="1">'
             + f'<tspan fill="{LINE2}">  /  </tspan>'.join(tools) + '</text>')
    save("disciplines.svg", "".join(b), W, H, "Level design and environment art skills")


# ---------------------------------------------------------------- PORTFOLIO TILE + CONTACT
def more_tile():
    W = H = 800
    b = [frame(W, H), grid(W, H, 50, "#13171c", "rt")]
    b.append(f'<g clip-path="url(#rt)">{contours(400, 420, 420, 9, 17, "#1a2027")}</g>')
    b.append(f'<text x="400" y="380" fill="{TEXT}" font-family="{SANS}" font-size="64" font-weight="700" '
             f'text-anchor="middle">Full portfolio</text>')
    b.append(f'<text x="400" y="440" fill="{ACC}" font-family="{MONO}" font-size="30" text-anchor="middle" '
             f'letter-spacing="2">artstation.com/cenk_k</text>')
    b.append(f'<path d="M370 520h60M410 500l20 20-20 20" fill="none" stroke="{ACC}" stroke-width="4"/>')
    save("tile-more.svg", "".join(b), W, H, "See the full portfolio on ArtStation")


def contact():
    W, H = 1600, 300
    b = [frame(W, H), grid(W, H, 40, "#12161b", "rc")]
    b.append(f'<g clip-path="url(#rc)">{contours(1350, 160, 380, 9, 29, "#1a2027")}</g>')
    b.append(f'<text x="80" y="104" fill="{MUTED}" font-family="{MONO}" font-size="15" letter-spacing="4">'
             f'OPEN TO LEVEL DESIGN / ENVIRONMENT ART ROLES</text>')
    b.append(f'<text x="76" y="190" fill="{TEXT}" font-family="{SANS}" font-size="64" font-weight="700" '
             f'letter-spacing="-1">artstation.com/cenk_k</text>')
    b.append(f'<path d="M80 232h64" stroke="{ACC}" stroke-width="4"/>')
    b.append(f'<g transform="translate(1180 150)"><circle r="56" fill="none" stroke="{ACC}" stroke-width="2.5"/>'
             f'<path d="M-20 0h40M6 -14l14 14-14 14" fill="none" stroke="{ACC}" stroke-width="3"/></g>')
    save("contact.svg", "".join(b), W, H, "Contact: artstation.com/cenk_k")


header()
section("h-about.svg", "01", "ABOUT")
section("h-pipeline.svg", "02", "PIPELINE")
section("h-skills.svg", "03", "DISCIPLINES")
section("h-work.svg", "04", "SELECTED WORK")
section("h-contact.svg", "05", "CONTACT")
pipeline()
disciplines()
more_tile()
contact()
print("ok")
