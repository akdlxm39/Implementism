# powershell alias

1. powershell 프로필 열기
   ```powershell
   code $PROFILE
   ```
2. `solve` alias 추가하기

   ```ps1
   function solve {
      Write-Host "🔍 저장소 상태 확인 중..." -ForegroundColor Cyan
      git fetch origin main -q

      # 1. 로컬 변경 사항(변동) 여부 확인
      $localChanges = git status --porcelain
      $hasLocalChanges = [bool]$localChanges

      # 2. 원격 저장소 확인 (가져올 Pull 여부)
      $behind = git rev-list --count HEAD..origin/main

      # 분기 1: 변동 없음 & Pull 없음
      if (-not $hasLocalChanges -and $behind -eq 0) {
         Write-Host "✅ 작업할 내용이 없습니다 (로컬과 원격 모두 최신 상태)." -ForegroundColor Green
         return
      }

      # 분기 2: 변동 없음 & Pull 있음
      if (-not $hasLocalChanges -and $behind -gt 0) {
         Write-Host "⬇️ 로컬 변동은 없으나 원격에 새 커밋이 있습니다. Pull을 진행합니다." -ForegroundColor Yellow
         git pull --rebase origin main
         Write-Host "✅ 동기화 완료." -ForegroundColor Green
         return
      }

      # --- 아래부터는 로컬에 '변동이 있는 경우' ---
      Write-Host "📦 로컬 변경 사항 커밋 중..." -ForegroundColor Cyan
      git add -A
      git commit -m "solve" | Out-Null # 불필요한 기본 커밋 로그 숨김

      # 분기 3: 변동 있음 & Pull 없음
      if ($behind -eq 0) {
         Write-Host "🚀 원격 저장소로 푸시합니다..." -ForegroundColor Cyan
         git push origin main
         return
      }

      # 분기 4: 변동 있음 & Pull 있음 (기존 Rebase + 안전장치)
      Write-Host "🔄 원격 업데이트가 존재합니다. 자동 병합을 시도합니다..." -ForegroundColor Yellow
      git pull --rebase origin main

      if ($LASTEXITCODE -ne 0) {
         Write-Host "❌ [오류] 자동 병합 중 충돌이 발생했습니다!" -ForegroundColor Red
         Write-Host "👉 충돌 해결 후 다음을 순서대로 입력하세요:" -ForegroundColor Yellow
         Write-Host "   1. git add 변경한파일"
         Write-Host "   2. git rebase --continue"
         Write-Host "   3. git push origin main"
         return
      }

      Write-Host "🚀 병합 완료! 원격 저장소로 푸시합니다..." -ForegroundColor Cyan
      git push origin main
   }
   ```

3. 만약 한글 깨짐이 생기면
   - vscode에서 $PROFILE 열기
   - vscode 우측 하단 `UTF-8` 클릭
   - `save with encoding` 선택
   - `UTF-8 with BOM`으로 다시 저장하기
   - powershell 재시작

# bash alias

1. bashrc 열기
   ```bash
   code ~/.bashrc
   ```
2. `solve` alias 추가하기

   ```bash
   function solve() {
      echo -e "\033[36m🔍 저장소 상태 확인 중...\033[0m"
      git fetch origin main -q

      # 1. 로컬 변경 사항(변동) 여부 확인
      local_changes=$(git status --porcelain)

      # 2. 원격 저장소 확인 (가져올 Pull 여부)
      behind=$(git rev-list --count HEAD..origin/main)

      # 분기 1: 변동 없음 & Pull 없음
      if [ -z "$local_changes" ] && [ "$behind" -eq 0 ]; then
         echo -e "\033[32m✅ 작업할 내용이 없습니다 (로컬과 원격 모두 최신 상태).\033[0m"
         return 0
      fi

      # 분기 2: 변동 없음 & Pull 있음
      if [ -z "$local_changes" ] && [ "$behind" -gt 0 ]; then
         echo -e "\033[33m⬇️ 로컬 변동은 없으나 원격에 새 커밋이 있습니다. Pull을 진행합니다.\033[0m"
         git pull --rebase origin main
         echo -e "\033[32m✅ 동기화 완료.\033[0m"
         return 0
      fi

      # --- 아래부터는 로컬에 '변동이 있는 경우' ---
      echo -e "\033[36m📦 로컬 변경 사항 커밋 중...\033[0m"
      git add -A
      git commit -m "solve" > /dev/null # 불필요한 기본 커밋 로그 숨김

      # 분기 3: 변동 있음 & Pull 없음
      if [ "$behind" -eq 0 ]; then
         echo -e "\033[36m🚀 원격 저장소로 푸시합니다...\033[0m"
         git push origin main
         return 0
      fi

      # 분기 4: 변동 있음 & Pull 있음 (기존 Rebase + 안전장치)
      echo -e "\033[33m🔄 원격 업데이트가 존재합니다. 자동 병합을 시도합니다...\033[0m"
      git pull --rebase origin main

      if [ $? -ne 0 ]; then
         echo -e "\033[31m❌ [오류] 자동 병합 중 충돌이 발생했습니다!\033[0m"
         echo -e "\033[33m👉 충돌 해결 후 다음을 순서대로 입력하세요:\033[0m"
         echo "   1. git add 변경한파일"
         echo "   2. git rebase --continue"
         echo "   3. git push origin main"
         return 1
      fi

      echo -e "\033[36m🚀 병합 완료! 원격 저장소로 푸시합니다...\033[0m"
      git push origin main
   }
   ```
