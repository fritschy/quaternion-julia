// https://www.shadertoy.com/view/MsfGRr

#include <MiniFB.h>

#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

//#include <glm/gtc/quaternion.hpp>

#include <ctime>
#include <vector>

#include <TaskScheduler.h>

#if 0
#include <glm/gtx/fast_exponential.hpp>
#include <glm/gtx/fast_square_root.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

#define log fastLog
#define pow fastPow
#define sin fastSin
#define cos fastCos
#define sqrt fastSqrt
#endif

namespace {

namespace approximate {
/* Approximation of f(x) = log(x)
 * on interval [ 0.001, 0.01 ]
 * with a polynomial of degree 3. */
float log001(float x) {
   float u = 4.9237523e+6f;
   u = u * x + -1.0793186e+5f;
   u = u * x + 8.9655674e+2f;
   return u * x + -7.6570452f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 0.01, 0.1 ]
 * with a polynomial of degree 3. */
float log01(float x) {
   float u = 4.9237523e+3f;
   u = u * x + -1.0793186e+3f;
   u = u * x + 8.9655674e+1f;
   return u * x + -5.3544601f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 0.1, 1 ]
 * with a polynomial of degree 3. */
float log1(float x) {
   float u = 4.9237523f;
   u = u * x + -1.0793186e+1f;
   u = u * x + 8.9655674f;
   return u * x + -3.051875f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 1, 10 ]
 * with a polynomial of degree 3. */
float log10(float x) {
   float u = 4.9237523e-3f;
   u = u * x + -1.0793186e-1f;
   u = u * x + 8.9655674e-1f;
   return u * x + -7.4928994e-1f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 10, 100 ]
 * with a polynomial of degree 3. */
float log100(float x) {
   float u = 4.9237523e-6f;
   u = u * x + -1.0793186e-3f;
   u = u * x + 8.9655674e-2f;
   return u * x + 1.5532951f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 100, 1000 ]
 * with a polynomial of degree 3. */
float log1000(float x) {
   float u = 4.9237523e-9f;
   u = u * x + -1.0793186e-5f;
   u = u * x + 8.9655674e-3f;
   return u * x + 3.8558802f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 1000, 10000 ]
 * with a polynomial of degree 3. */
float log10000(float x) {
   float u = 4.9237523e-12f;
   u = u * x + -1.0793186e-7f;
   u = u * x + 8.9655674e-4f;
   return u * x + 6.1584653f;
}

/* Approximation of f(x) = log(x)
 * on interval [ 1/1024, 1/128 ]
 * with a polynomial of degree 3. */
float log0128(float x) {
   float u = 8.4613609e+6f;
   u = u * x + -1.5063532e+5f;
   u = u * x + 1.0390709e+3f;
   return u * x + -7.7798414f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 1/128, 1/32 ]
 * with a polynomial of degree 3. */
float log032(float x) {
   float u = 6.580625e+4f;
   u = u * x + -5.474308e+3f;
   u = u * x + 1.8864233e+2f;
   return u * x + -6.0164018f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 1/32, 1/8 ]
 * with a polynomial of degree 3. */
float log08(float x) {
   float u = 1.0282226e+3f;
   u = u * x + -3.4214425e+2f;
   u = u * x + 4.7160582e+1f;
   return u * x + -4.6301074f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 1/8, 1/2 ]
 * with a polynomial of degree 3. */
float log02(float x) {
   float u = 1.6065979e+1f;
   u = u * x + -2.1384016e+1f;
   u = u * x + 1.1790146e+1f;
   return u * x + -3.2438131f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 1/2, 2 ]
 * with a polynomial of degree 3. */
float log2(float x) {
   float u = 2.5103092e-1f;
   u = u * x + -1.336501f;
   u = u * x + 2.9475364f;
   return u * x + -1.8575187f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 2, 8 ]
 * with a polynomial of degree 3. */
float log8(float x) {
   float u = 3.9223581e-3f;
   u = u * x + -8.3531312e-2f;
   u = u * x + 7.3688409e-1f;
   return u * x + -4.7122433e-1f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 8, 32 ]
 * with a polynomial of degree 3. */
float log32(float x) {
   float u = 6.1286846e-5f;
   u = u * x + -5.220707e-3f;
   u = u * x + 1.8422102e-1f;
   return u * x + 9.1507003e-1f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 32, 128 ]
 * with a polynomial of degree 3. */
float log128(float x) {
   float u = 9.5760696e-7f;
   u = u * x + -3.2629419e-4f;
   u = u * x + 4.6055256e-2f;
   return u * x + 2.3013644f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 128, 1024 ]
 * with a polynomial of degree 3. */
float log1024(float x) {
   float u = 3.7575991e-9f;
   u = u * x + -8.7681296e-6f;
   u = u * x + 7.9274819e-3f;
   return u * x + 4.0036607f;
}
/* Approximation of f(x) = log(x)
 * on interval [ 1024, 8192 ]
 * with a polynomial of degree 3. */
float log8192(float x) {
   float u = 7.3390607e-12f;
   u = u * x + -1.3700203e-7f;
   u = u * x + 9.9093524e-4f;
   return u * x + 6.0831023f;
}

float log(float x) {
   // XXX
   /* union { */
   /*    uint32_t u; */
   /*    float f; */
   /* } l; */
   /* l.f = x; */
   /* switch ((signed int)(((l.u >> 23) & 0xff) - 127)) { */
   /*    case -9: case -8: case -7: return log0128(x); */
   /*    case -6: case -5: return log032(x); */
   /*    case -4: case -3: return log08(x); */
   /*    case -2: case -1: return log02(x); */
   /*    case 0: case 1: return log2(x); */
   /*    case 2: case 3: return log8(x); */
   /*    case 4: case 5: return log32(x); */
   /*    case 6: case 7: return log128(x); */
   /*    case 8: case 9: case 10: return log1024(x); */
   /*    case 11: case 12: case 13: return log8192(x); */
   /* } */

   // XXX
   /* if (x < 1.0 / 128.0) return log0128(x); */
   /* if (x < 1.0 / 32.0) return log032(x); */
   /* if (x < 1.0 / 8.0) return log08(x); */
   /* if (x < 1.0 / 2.0) return log02(x); */
   /* if (x < 2.0) return log2(x); */
   /* if (x < 8.0) return log8(x); */
   /* if (x < 32.0) return log32(x); */
   /* if (x < 128.0) return log128(x); */
   /* if (x < 1024.0) return log1024(x); */
   /* if (x < 8192.0) return log8192(x); */

#if 1
#define unlikely(x) __builtin_expect(x, 0)
#else
#define unlikely(x) (x)
#endif

   // XXX
   if (x < 10) {
      if (x < 1) {
         if (x < 0.1) {
            if (x < 0.01) {
               return log001(x);
            }
            return log01(x);
         }
         return log1(x);
      }
      return log10(x);
   }
   if (x < 1000) {
      if (x < 100)
         return log100(x);
      return log1000(x);
   }
   if (x < 10000)
      return log10000(x);

/*    if (unlikely(x < 0.01)) */
/*       return log001(x); */
/*    if (unlikely(x < 0.1)) */
/*       return log01(x); */
/*    if (unlikely(x < 1)) */
/*       return log1(x); */
/*    if (unlikely(x < 10)) */
/*       return log10(x); */
/*    if (unlikely(x < 100)) */
/*       return log100(x); */
/*    if (unlikely(x < 1000)) */
/*       return log1000(x); */
/*    if (unlikely(x < 10000)) */
/*       return log10000(x); */

   return glm::log(x);
}
}

using namespace glm;

constexpr int AA = 1;

float iGlobalTime;
vec2 iResolution;
vec4 c;

float map(vec3 p, vec4 *oTrap) {
   vec4 z = vec4(p, 0.0f);
   float md2 = 1.0f;
   float mz2 = dot(z, z);
   vec4 nz;

   vec4 trap;
   if (oTrap)
      trap = vec4(abs(z.xyz()), dot(z, z));

   for (int i = 0; i < 11; i++) {
      // |dz|^2 -> 4*|dz|^2
      md2 *= 4.0f * mz2;

      // z -> z2 + c
      nz.x = z.x * z.x - dot(z.yzw(), z.yzw());
      vec3 yzw = 2.0f * z.x * z.yzw();
      nz.y = yzw.x;
      nz.z = yzw.y;
      nz.w = yzw.z;
      z = nz + c;

      if (oTrap)
         trap = min(trap, vec4(abs(z.xyz()), dot(z, z)));

      mz2 = dot(z, z);
      if (mz2 > 4.0f) {
         break;
      }
   }

   /* printf("%f\n", mz2 / md2); */

   float ret = 0.25f * sqrt(mz2 / md2) * approximate::log(mz2);

   if (oTrap)
      *oTrap = trap;

   /* if (ret < 10) */
   /*    printf("%f\n", mz2); */
   return ret;
}

// analytical normal for quadratic formula
vec3 calcNormal(vec3 p) {
   vec4 nz, ndz;

   vec4 z = vec4(p, 0.0f);

   vec4 dz0 = vec4(1.0f, 0.0f, 0.0f, 0.0f);
   vec4 dz1 = vec4(0.0f, 1.0f, 0.0f, 0.0f);
   vec4 dz2 = vec4(0.0f, 0.0f, 1.0f, 0.0f);
   vec4 dz3 = vec4(0.0f, 0.0f, 0.0f, 1.0f);

   for (int i = 0; i < 11; i++) {
      vec4 mz = vec4(z.x, -z.y, -z.z, -z.w);

      // derivative
      dz0 = vec4(dot(mz, dz0), z.x * dz0.yzw() + dz0.x * z.yzw());
      dz1 = vec4(dot(mz, dz1), z.x * dz1.yzw() + dz1.x * z.yzw());
      dz2 = vec4(dot(mz, dz2), z.x * dz2.yzw() + dz2.x * z.yzw());
      dz3 = vec4(dot(mz, dz3), z.x * dz3.yzw() + dz3.x * z.yzw());

      // z = z2 + c
      nz.x = dot(z, mz);
      vec3 yzw = 2.0f * z.x * z.yzw();
      nz.y = yzw.x;
      nz.z = yzw.y;
      nz.w = yzw.z;
      z = nz + c;

      if (dot(z, z) > 4.0f)
         break;
   }

   return normalize(vec3(dot(z, dz0), dot(z, dz1), dot(z, dz2)));
}

float intersect(vec3 ro, vec3 rd, vec4 &res) {
   vec4 tmp;
   float resT = -1.0f;
   float maxd = 10.0f;
   float h = 1.0f;
   float t = 0.0f;
   int i;
   for (i = 0; i < 150; i++) {
      if (h < 0.002f || t > maxd)
         break;
      h = map(ro + rd * t, &tmp);
      t += h;
   }
   /* printf("%d\n", i); */
   if (t < maxd) {
      resT = t;
      res = tmp;
   }

   return resT;
}

float softshadow(vec3 ro, vec3 rd, float mint, float k) {
   float res = 1.0f;
   float t = mint;
   for (int i = 0; i < 64; i++) {
      float h = map(ro + rd * t, NULL);
      res = min(res, k * h / t);
      if (res < 0.001f)
         break;
      t += clamp(h, 0.01f, 0.5f);
   }
   return clamp(res, 0.0f, 1.0f);
}

vec3 render(vec3 ro, vec3 rd) {
   vec3 light1 = vec3(0.577f, 0.577f, 0.577f);
   vec3 light2 = vec3(-0.707f, 0.000f, -0.707f);

   vec4 tra;
   vec3 col;
   float t = intersect(ro, rd, tra);
   if (t < 0.0f) {
      col = vec3(0.8f, 0.9f, 1.0f) * (0.7f + 0.3f * rd.y);
      col += vec3(0.8f, 0.7f, 0.5f) *
             pow(clamp(dot(rd, light1), 0.0f, 1.0f), 48.0f);
   } else {
      vec3 pos = ro + t * rd;
      vec3 nor = calcNormal(pos);
      vec3 ref = reflect(rd, nor);

      float dif1 = clamp(dot(light1, nor), 0.0f, 1.0f);
      float dif2 = clamp(0.5f + 0.5f * dot(light2, nor), 0.0f, 1.0f);
      float ao = clamp(2.5f * tra.w - 0.15f, 0.0f, 1.0f);

      float sha = softshadow(pos, light1, 0.001f, 64.0f);

      float fre = pow(clamp(1.f + dot(rd, nor), 0.0f, 1.0f), 2.0f);

      float pa = 0.0f;  // smoothstep(0.1f,0.2f,length(tra.xyz));
      col = vec3(1.0f, 0.8f, 0.7f) * 0.3f;
      col = mix(col, vec3(0.0f), pa);

      vec3 lin = 1.5f * vec3(0.15f, 0.20f, 0.25f) * (0.6f + 0.4f * nor.y) *
                 (0.1f + 0.9f * ao);
      lin += 3.5f * vec3(1.00f, 0.90f, 0.70f) * dif1 * sha;
      lin += 1.5f * vec3(0.14f, 0.14f, 0.14f) * dif2 * ao;
      lin += 0.3f * vec3(1.00f, 0.80f, 0.60f) * fre;
      col *= lin;
      col += pow(clamp(dot(ref, light1), 0.0f, 1.0f), 32.0f) * dif1 * sha;
      col += (1.0f - pa) * 0.1f * vec3(0.8f, 0.9f, 1.0f) *
             smoothstep(0.0f, 0.1f, ref.y) * ao * (0.5f + 0.5f * nor.y);
   }

   return sqrt(col);
}

void mainImage(vec3 ro, vec3 ta, float cr, vec4 &fragColor, vec2 fragCoord) {
   vec3 col = vec3(0.0f);
   for (int j = 0; j < AA; j++)
      for (int i = 0; i < AA; i++) {
         vec2 p =
            (-iResolution.xy() +
             2.0f * (fragCoord.xy() + vec2(float(i), float(j)) / float(AA))) /
            iResolution.y;

         vec3 cw = normalize(ta - ro);
         vec3 cp = vec3(sin(cr), cos(cr), 0.0f);
         vec3 cu = normalize(cross(cw, cp));
         vec3 cv = normalize(cross(cu, cw));
         vec3 rd = normalize(p.x * cu + p.y * cv + 2.0f * cw);

         col += render(ro, rd);
      }
   col /= float(AA * AA);

   vec2 uv = fragCoord.xy() / iResolution.xy();
   col *=
      0.7f +
      0.3f * pow(16.0f * uv.x * uv.y * (1.0f - uv.x) * (1.0f - uv.y), 0.25f);

   fragColor = vec4(col, 1.0f);
}

void frame(enki::TaskScheduler *ts, std::vector<uint32_t> *buf, int w, int h) {
   // anim
   float time = iGlobalTime * .15f;
   c = 0.4f * cos(vec4(0.5f, 3.9f, 1.4f, 1.1f) +
                  time * vec4(1.2f, 1.7f, 1.3f, 2.5f)) -
       vec4(0.3f, 0.0f, 0.0f, 0.0f);

   // camera
   float r = 1.4f + 0.15f * cos(0.0f + 0.29f * time);
   vec3 ro = vec3(r * cos(0.3f + 0.37f * time),
                  0.3f + 0.8f * r * cos(1.0f + 0.33f * time),
                  r * cos(2.2f + 0.31f * time));
   vec3 ta = vec3(0.0f, 0.0f, 0.0f);
   float cr = 0.1f * cos(0.1f * time);

#ifdef USE_ENKITS
#define TILE_SIZE 8
   enki::TaskSet t(
      h / TILE_SIZE + h % TILE_SIZE,
      [h, w, ro, ta, cr, buf](enki::TaskSetPartition range, uint32_t) {
         vec4 fragColor;
         for (unsigned y = range.start * TILE_SIZE,
                       yend = min(int(h), int(range.end * TILE_SIZE));
              y < yend; y++)
            for (unsigned x = 0; x < w; x++) {
               mainImage(ro, ta, cr, fragColor, vec2(x, y));
               fragColor = clamp(fragColor, vec4(0), vec4(1));
               fragColor *= 255.f;
               (*buf)[(h - 1 - y) * w + x] =
                  MFB_RGB(uint8_t(fragColor.r), uint8_t(fragColor.g),
                          uint8_t(fragColor.b));
            }
      });
   ts->AddTaskSetToPipe(&t);

   ts->WaitforAll();
#else
#ifdef USE_OPENMP
// http://web.archive.org/web/20160730003601/https://software.intel.com/en-us/articles/openmp-loop-scheduling
#pragma omp parallel for schedule(guided)
#endif
   for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
         vec4 fragColor;
         mainImage(ro, ta, cr, fragColor, vec2(x, y));
         fragColor = clamp(fragColor, vec4(0), vec4(1));
         fragColor *= 255.f;
         (*buf)[(h - 1 - y) * w + x] = MFB_RGB(
            uint8_t(fragColor.r), uint8_t(fragColor.g), uint8_t(fragColor.b));
      }
   }
#endif
}

float seconds() {
   struct timespec tv;
   clock_gettime(CLOCK_MONOTONIC, &tv);
   return tv.tv_sec + tv.tv_nsec / 1e9f;
}

}  //  namespace

int main(int argc, char **argv) {
   std::vector<uint32_t> buf;
   constexpr int w = 800;
   constexpr int h = 600;
   buf.resize(w * h);

   iResolution = vec2(w, h);

   if (!mfb_open("Quaternion Julia", w, h))
      return 1;

   enki::TaskScheduler ts;
   ts.Initialize();

   std::function<float()> next_time_step = [] {
      static float t_offset = seconds();
      return seconds() - t_offset;
   };
   std::function<bool()> should_continue = [] { return 1; };

   // I am a lazy person...
   if (argv[1]) {
      next_time_step = [] {
         static float t;
         return t += 1;
      };
      should_continue = [argv] {
         static int i;
         static bool first = true;
         if (first) {
            first = false;
            i = atoi(argv[1]);
         }
         return !!i--;
      };
   }

   while (should_continue()) {
      frame(&ts, &buf, w, h);
      int state = mfb_update((uint8_t *)buf.data());
      if (state < 0)
         break;
      iGlobalTime = next_time_step();
   }

   mfb_close();

   return 0;
}
