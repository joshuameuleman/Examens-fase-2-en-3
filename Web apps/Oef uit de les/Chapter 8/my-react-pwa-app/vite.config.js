import { VitePWA } from 'vite-plugin-pwa';
import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import mkcert from 'vite-plugin-mkcert'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [react(), mkcert(), VitePWA({
    registerType: 'prompt',
    injectRegister: false,

    pwaAssets: {
      disabled: false,
      config: true,
    },

    manifest: {
      name: 'my-react-pwa-app',
      short_name: 'my-react-pwa-app',
      description: 'my-react-pwa-app',
      theme_color: '#ffffff',
      start_url: '/',
      display: 'fullscreen', //'standalone'
    },

    workbox: {
      globPatterns: ['**/*.{js,css,html,svg,png,ico}'],
      cleanupOutdatedCaches: true,
      clientsClaim: true,
    },

    devOptions: {
      enabled: false,
      navigateFallback: 'index.html',
      suppressWarnings: true,
      type: 'module',
    },
  })],
  server: {
    https: true, // als je mkcert gebruikt
    host: '0.0.0.0', // om het even welk ip-adres connecteert met deze server
  },
})
